#include "secondary.h"
#include "function_declares.h"
#include <stdio.h>
#include <pthread.h>

void* add(int a);
int main(int argc, char* argv[]){
    void* states[] = {&&state_A,&&state_B,&&state_C,};

    if(argc > 1){
        void* ptr = states[atoi(argv[1])];
        goto *ptr;
    }
    int x = 9, i = 1;
state_A:
    printf("X = %d, I = %d\n",x,i);
    pthread_t add_thread;
    void* status;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&add_thread, &attr, add, (int) &x);
    pthread_join(add_thread, &status);
    printf("x = %d i = %d",x,i);
    goto state_B;


    int q;
state_B:
    goto state_C;


state_C:
    return 0;
    goto state_C;

}

void* add(int a){
    int b = 0;
    printf("x = %d i = %d\n", a, b);
    return a + b;
}
