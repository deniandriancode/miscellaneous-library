#include <stdio.h>
#include <stdlib.h>
#include <portaudio.h>

#define NUM_SECONDS (5)
#define NUM_CHANNELS (2)
#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (512)

/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

typedef struct
{
	int frameIndex;	/* index into sample array */
	int maxFrameIndex;
	SAMPLE *recordedSamples;
}
paTestData;

static int playCallback (const void *inputBuf, void *outputBuf,
			 unsigned long framesPerBuf,
			 const PaStreamCallbackTimeInfo *timeInfo,
			 PaStreamCallbackFlags statusFlags,
			 void *userData);

int
main (int argc, char **argv)
{
	PaStreamParameters  inputParameters, outputParameters;
	PaStream*           stream;
	PaError             err = paNoError;
	paTestData          data;
	int                 i;
	int                 totalFrames;
	int                 numSamples;
	int                 numBytes;
	SAMPLE              max, val;
	double              average;

	fflush(stdout);
   
	data.maxFrameIndex = totalFrames = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
    data.frameIndex = 0;
    numSamples = totalFrames * NUM_CHANNELS;
    numBytes = numSamples * sizeof(SAMPLE);
    data.recordedSamples = (SAMPLE *) malloc( numBytes ); /* From now on, recordedSamples is initialised. */
    if( data.recordedSamples == NULL )
    {
        printf("Could not allocate record array.\n");
        goto done;
    }
    for( i=0; i<numSamples; i++ ) data.recordedSamples[i] = 0;
   
    err = Pa_Initialize();
    if( err != paNoError ) goto done;
   
    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    if (inputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default input device.\n");
        goto done;
    }
    inputParameters.channelCount = 2;                    /* stereo input */
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

	/* Playback recorded data.  -------------------------------------------- */
	data.frameIndex = 0;

	outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
	if (outputParameters.device == paNoDevice) {
		fprintf(stderr,"Error: No default output device.\n");
		goto done;
	}
	outputParameters.channelCount = 2;                     /* stereo output */
	outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	printf("\n=== Now playing back. ===\n"); fflush(stdout);
	err = Pa_OpenStream(
		&stream,
		NULL, /* no input */
		&outputParameters,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,      /* we won't output out of range samples so don't bother clipping them */
		playCallback,
		&data );
	if( err != paNoError ) goto done;

	if( stream ) {
		err = Pa_StartStream( stream );
		if( err != paNoError ) goto done;

		printf("Waiting for playback to finish.\n"); fflush(stdout);

		while( ( err = Pa_IsStreamActive( stream ) ) == 1 ) Pa_Sleep(100);
		if( err < 0 ) goto done;

		err = Pa_CloseStream( stream );
		if( err != paNoError ) goto done;

		printf("Done.\n"); fflush(stdout);
	}
done:
	Pa_Terminate();
	if( data.recordedSamples )       /* Sure it is NULL or valid. */
		free( data.recordedSamples );
	if( err != paNoError ) {
		fprintf( stderr, "An error occured while using the portaudio stream\n" );
		fprintf( stderr, "Error number: %d\n", err );
		fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
		err = 1;          /* Always return 0 or 1, but no other return codes. */
	}
	return 0;
}

static int
playCallback (const void *inputBuf, void *outputBuf,
			 unsigned long framesPerBuf,
			 const PaStreamCallbackTimeInfo *timeInfo,
			 PaStreamCallbackFlags statusFlags,
			 void *userData)
{
	paTestData *data = (paTestData *) userData;
	SAMPLE *rptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
	SAMPLE *wptr = (SAMPLE *) outputBuf;
	unsigned int i;
	int finished;
	unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;

	(void) inputBuf; /* prevent unused variable warnings. */
	(void) timeInfo;
	(void) statusFlags;
	(void) userData;

	if (framesLeft < framesPerBuf) {
		/* final buffer... */
		for (i = 0; i < framesLeft; ++i) {
			*wptr++ = *rptr++; /* left */
			if (NUM_CHANNELS == 2) *wptr++ = *rptr++; /* right */
		}
		for (i; i < framesPerBuf; ++i) {
			*wptr++ = 0; /* left */
			if (NUM_CHANNELS == 2) *wptr++ = 0; /* right */
		}
		data->frameIndex += framesLeft;
		finished = paComplete;
	} else {
		for (i = 0; i < framesPerBuf; ++i) {
			*wptr++ = *rptr++; /* left */
			if (NUM_CHANNELS == 2) *wptr++ = *rptr++; /* right */
		}
		data->frameIndex += framesPerBuf;
		finished = paContinue;
	}
	return finished;
}
