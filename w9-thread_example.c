#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 10

void *multiply(void *arg)
{
    int *pi = (int *)arg;
    printf("%d: Hello-i:%ld\n",pthread_self(), *pi);
    pthread_exit(0);
}

int main(void)
{
    pthread_t thread[NUM_THREADS];
    long a = 5;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&thread[i], NULL, multiply, &i);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(thread[i], NULL);  
    }

    return 0;
}
