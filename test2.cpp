#include <pthread.h>
#include <cstdio>

void* Test(void* args)
{
    int* ptr = (int*)args;

    printf("[thread]pointer is %p\n", ptr);
    printf("[thread]value is %d\n", *ptr);

    return 0;
}

int main()
{
    int* ptr = nullptr;
    int i = 50;
    ptr = &i;

    pthread_t thread;
    pthread_create(&thread, NULL, Test, (void*)ptr);

    printf("pointer is %p\n", ptr);
    printf("value is %d\n", *ptr);

    return 0;
}