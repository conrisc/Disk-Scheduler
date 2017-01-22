#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <list>

using namespace std;

int max_disk_queue, active;
sem_t coutMut, disk_queue, serv_block, reqMut;
list<int> requests;

typedef struct {
  int id;
  string *fileName;
} ReqInfo;

void *requester(void *arg) {
  ReqInfo* ri = (ReqInfo*)arg;
  ifstream file;
  file.open( (*(ri->fileName)).c_str() );
  string reqLine;
  int free_slots_in_queue;
  while (getline( file, reqLine )) {
    // sem_wait(&req[id]);
    sem_wait(&reqMut);
    sem_wait(&disk_queue);
    sem_wait(&coutMut);
    cout << "requester " << ri->id << " track " << reqLine << endl;
    sem_post(&coutMut);
    sem_getvalue(&disk_queue,&free_slots_in_queue);
    if (free_slots_in_queue == 0 || max_disk_queue - active == free_slots_in_queue) {
      sem_post(&serv_block);
    }
    sem_post(&reqMut);
  }
  sem_wait(&reqMut);
  active--;
  if (active==0) sem_post(&serv_block);
  sem_post(&reqMut);
  file.close();
  delete (ReqInfo*)arg;
  pthread_exit(NULL);
}

void *service(void *sth) {
  while (true) {
    if (active!=0) sem_wait(&serv_block);
    sem_wait(&coutMut);
    // sem_post(&req[id]);
    sem_post(&disk_queue);
    cout << "service requester " << "SOME_REQUESTER" << " track " << "SOME_TRACK" << endl;
    sem_post(&coutMut);
  }
  pthread_exit(NULL);
}

int main( int argc, char * argv[] ) {

  if (argc<3) return 1;

  max_disk_queue = atoi(argv[1]);
  active = argc-2;
  pthread_t threads[argc-1];

  sem_init(&coutMut, 0, 1);
  sem_init(&reqMut, 0, 1);
  sem_init(&serv_block,0,0);
  sem_init(&disk_queue,0,max_disk_queue);
  for (int i=0;i<active;i++) {
    // sem_init(&req[i],0,1);
  }

  pthread_create(&threads[0], NULL, service, NULL);


  for (long i = 1; i < argc-1; i++) {
    ReqInfo *ri = new ReqInfo;
    ri -> id = i;
    ri -> fileName = new string(argv[i+1]);
    cout<<ri -> id<<endl;
    pthread_create(&threads[i], NULL, requester, (void *) ri);
  }

  for (int i = 0; i < argc-1; i++)
    pthread_join(threads[i], NULL);

  return 0;
}
