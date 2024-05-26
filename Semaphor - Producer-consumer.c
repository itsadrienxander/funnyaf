#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 20

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int produced_count = 0;
int consumed_count = 0;

sem_t mutex;  //ensures only on thread acess at a time
sem_t full;  //keep track of how many slots in the buffer are full
sem_t empty;  //keep track of how many slots are empty.

void* producer(void* arg) {
   int item = 1;

   while (produced_count < MAX_ITEMS) {
      sem_wait(&empty);//producer waits until the buffer is empty
      sem_wait(&mutex);//then it waits until it can acess the buffer

      buffer[in] = item;//adding the item to the buffer
      printf("Produced: %d\n", item);
      item++;
      in = (in + 1) % BUFFER_SIZE;

      produced_count++;

      sem_post(&mutex);
      sem_post(&full);
   }

   pthread_exit(NULL);
}

void* consumer(void* arg) {// removes data from the buffer and uses the same semaphores to coordinate with the producer.
   while (consumed_count < MAX_ITEMS) {
      sem_wait(&full);
      sem_wait(&mutex);

      int item = buffer[out];
      printf("Consumed: %d\n", item);
      out = (out + 1) % BUFFER_SIZE;

      consumed_count++;

      sem_post(&mutex);
      sem_post(&empty);
   }

   pthread_exit(NULL);
}

int main() {
   pthread_t producerThread, consumerThread;

   sem_init(&mutex, 0, 1);
   sem_init(&full, 0, 0);
   sem_init(&empty, 0, BUFFER_SIZE);

   pthread_create(&producerThread, NULL, producer, NULL);
   pthread_create(&consumerThread, NULL, consumer, NULL);

   pthread_join(producerThread, NULL);
   pthread_join(consumerThread, NULL);

   sem_destroy(&mutex);
   sem_destroy(&full);
   sem_destroy(&empty);

   return 0;
}
