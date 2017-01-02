#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <string>

using namespace std;

sem_t coutMut;

void *requester(void *file) {
  std::string* inputFile= reinterpret_cast<std::string*>(file);
  sem_wait(&coutMut);
  cout<<*inputFile<<endl;
  sem_post(&coutMut);
  // while (file) {

  // }
  pthread_exit(NULL);
}

void *service(void *sth) {
  // while (requests) {

  // }
  pthread_exit(NULL);
}

int main( int argc, char * argv[] ) {

  sem_init(&coutMut, 0, 1);

  pthread_t threads[argc-1];

  pthread_create(&threads[0], NULL, service, NULL);

  for (long i = 1; i < argc-1; i++) {
    string *parm = new string(argv[i+1]);
    pthread_create(&threads[i], NULL, requester, (void *) parm);
  }

  for (int i = 0; i < argc-1; i++)
    pthread_join(threads[i], NULL);

  return 0;
}
