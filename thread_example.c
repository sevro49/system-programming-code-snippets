#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 10

void *multiply(void *arg)
{
    int *p = (int *)arg;
    printf("%d: Hello-a:%d\n",pthread_self(), *p);
    pthread_exit(0);
}

int main(void)
{
    pthread_t thread[NUM_THREADS];
    int a = 5;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&thread[i], NULL, multiply, &a);
        pthread_join(thread[i], NULL);
    }
    return 0;
}
