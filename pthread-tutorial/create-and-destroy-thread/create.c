#include <pthread.h>

void* thread_function (void *arg);

int
main ()
{
        pthread_t thread_id;
        void *thread_result;
        int value;

        value = 42;

        pthread_create (&thread_id, NULL, thread_function, &value);

        pthread_join (thread_id, &thread_result);

        return 0;
}

void*
thread_function (void *arg)
{
        int *incoming = (int *) arg;
        return NULL;
}
