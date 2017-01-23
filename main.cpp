// Konrad Cielecki, nr indeksu: 273278
// Pracownia z Systemów operacyjnych nr 2

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <list>

using namespace std;

int max_disk_queue, active, requestsQueue[1000], requestsSent;
sem_t coutMut, disk_queue, serv_block, reqMut, *reqr;

typedef struct {
  int id;
  string *fileName;
} ReqrInfo;

void *requester(void *arg) {
  ReqrInfo* ri = (ReqrInfo*)arg;
  ifstream file;
  file.open( (*(ri->fileName)).c_str() );
  string reqLine;
  while (getline( file, reqLine )) {
    sem_wait(&reqr[ ri->id -1 ]);
    sem_wait(&disk_queue);
    sem_wait(&reqMut);
    requestsQueue[atoi(reqLine.c_str())] = ri->id;
    requestsSent++;
    sem_wait(&coutMut);
    cout << "requester " << ri->id << " track " << reqLine << endl;
    sem_post(&coutMut);
    if (requestsSent == max_disk_queue || requestsSent == active) {
      sem_post(&serv_block);
    }
    sem_post(&reqMut);
  }
  sem_wait(&reqr[ ri-> id - 1]);
  sem_wait(&reqMut);
  active--;
  if (requestsSent == max_disk_queue || requestsSent == active) sem_post(&serv_block);
  sem_post(&reqMut);
  file.close();
  delete (ReqrInfo*)arg;
  pthread_exit(NULL);
}

void *service(void *sth) {
  int track = 0, requesterID;
  bool up = true;
  while (active>0) {
    sem_wait(&serv_block);
    while (requestsSent != max_disk_queue && requestsSent!=active) {}
    for(int j=0;requestsQueue[track]==0 && j<2000;j++) {
      if (track == 0) up = true;
      else if (track == 999) up = false;
      if (up) track++;
      else track--;
    }
    requesterID = requestsQueue[track];
    if (requesterID>0) {
      sem_wait(&reqMut);
      requestsQueue[track] = 0;
      requestsSent--;
      sem_wait(&coutMut);
      sem_post(&reqr[requesterID - 1]);
      sem_post(&disk_queue);
      cout << "service requester " << requesterID << " track " << track << endl;
      sem_post(&coutMut);
      sem_post(&reqMut);
    }
  }
  pthread_exit(NULL);
}

int main( int argc, char * argv[] ) {

  if (argc<3) return 1;

  requestsSent = 0;
  max_disk_queue = atoi(argv[1]);
  active = argc-2;
  pthread_t threads[argc-1];
  reqr = new sem_t[active];

  sem_init(&coutMut, 0, 1);
  sem_init(&reqMut, 0, 1);
  sem_init(&serv_block,0,0);
  sem_init(&disk_queue,0,max_disk_queue);
  for (int i=0;i<active;i++) {
     sem_init(&(reqr[i]),0,1);
  }

  pthread_create(&threads[0], NULL, service, NULL);

  for (long i = 1; i < argc-1; i++) {
    ReqrInfo *ri = new ReqrInfo;
    ri -> id = i;
    ri -> fileName = new string(argv[i+1]);
    pthread_create(&threads[i], NULL, requester, (void *) ri);
  }

  for (int i = 0; i < argc-1; i++)
    pthread_join(threads[i], NULL);

  return 0;
}
