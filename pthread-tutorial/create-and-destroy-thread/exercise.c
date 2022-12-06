#include <stdio.h>
#include <pthread.h>

void* thread_function (void *arg);

int
main ()
{
        int i;
        pthread_t threads[10];
        void *thread_result[10];

        for (i = 0; i < 10; ++i)
                pthread_create (&(threads[i]), NULL, thread_function, &i);

        for (i = 0; i < 10; ++i)
                pthread_join (threads[i], &(thread_result[i]));

        return 0;
}

void*
thread_function (void *arg)
{
        int i;
        int *num = (int *) arg;

        for (i = 0; i < 5; ++i)
                printf ("Hello wolrd (thread %d)\n", *num);

        return NULL;
}
