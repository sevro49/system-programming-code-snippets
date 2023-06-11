#include <pthread.h>
#include <stdio.h>

void *goldcount(void *args){
    long order = (long) args;
    printf("Hello from thread order-id: %ld-%ld\n", order, pthread_self());

    pthread_exit(NULL);
}

int main(int argc, char *argv){
    pthread_t threads[5] = {0};
    pthread_create(&threads[0], NULL, goldcount, (void *)0);

    pthread_join(threads[0], NULL);
    return 0;
}
