#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

pthread_t tid1,tid2,tid3;

void *hi(void *arg){
    int i;
    for(i=1;i<=100;i++){
        printf("hi\t");
    }
    printf("\n");
    return ((void *)0);
}

void *hello(void *arg){
    int j;
    for(j=1;j<=100;j++){
        printf("he \t");
    }
    printf("\n");
    return ((void *)0);
}

void main(){
    int err;
    err = pthread_create(&tid1,NULL,hi,NULL);
    if(err != 0){
        printf("Error");
    }
    err = pthread_create(&tid2,NULL,hello,NULL);
    if(err != 0){
        printf("Error");
    }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    exit(0);
}



