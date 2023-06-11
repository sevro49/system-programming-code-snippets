#include <pthread.h>
#include <stdio.h>

void *goldcount(void *args){
    long order = (long) args;
    printf("id: %ld- Hello from thread order-id: %ld\n", order, pthread_self());

    exit(0);
}

int main(int argc, char *argv[]){
    pthread_t threads[5] = {0};
    pthread_create(&threads[0], NULL, goldcount, (void *)0);

    pthread_join(threads[0], NULL);
    printf("main: hello\n");
    return 0;
}
