/*#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t mutex, writeblock;
int data = 0 , rcount = 0;

void *reader(void *arg){
int f;
f=((int)arg);
sem_wait(&mutex);
rcount+=1;
}

void *writer(void *arg){
int f;
f = ((int)arg);
sem_wait(&writeblock);
data++;
printf("data written by write %d is %d\n", f,data);
sleep();
sem_post(&writeblock); 
}

int main(){
pthread_t rtid[5] , wtid[5];
sem_int(&mutex, 0,1);
sem_int(&mutex, 1,2);
}*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

char buffer[BUFFER_SIZE];
int buffer_index;
sem_t sem;

void *writer(void *param) {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    sem_wait(&sem); // wait for semaphore to be available
    buffer[buffer_index++] = 'a' + i;
    printf("Writer wrote %c to buffer.\n", buffer[buffer_index-1]);
    sem_post(&sem); // signal semaphore
  }
  pthread_exit(NULL);
}

void *reader(void *param) {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    sem_wait(&sem); // wait for semaphore to be available
    printf("Reader read %c from buffer.\n", buffer[--buffer_index]);
    sem_post(&sem); // signal semaphore
  }
  pthread_exit(NULL);
}

int main() {
  pthread_t writer_thread, reader_thread;
  sem_init(&sem, 0, 1); // initialize semaphore

  buffer_index = 0;
  pthread_create(&writer_thread, NULL, writer, NULL);
  pthread_create(&reader_thread, NULL, reader, NULL);

  pthread_join(writer_thread, NULL);
  pthread_join(reader_thread, NULL);

  sem_destroy(&sem); // destroy semaphore
  return 0;
}

