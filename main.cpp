#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <string>

using namespace std;

void *requester(void *file) {
  //string inputFile = (string)file;
  std::string* inputFile= reinterpret_cast<std::string*>(file);
  cout<<inputFile<<endl;
  // while (true) {
  //   #ifdef SLEEP_ENABLED
  //     randsleep();
  //   #endif
  //   sem_wait(&gnomes);
  //   if (firstPartNotCreated) {
  //     createdToy = gID;
  //     firstPartNotCreated=false;
  //     cout << "gnome" << gID+1 << "(): Zacząłem produkcję zabawki.\n";
  //     blockedGnome=gID;
  //     sem_post(&gnomes);
  //     sem_wait(&gnomeSem[gID]);
  //   }
  //   else {
  //     createdToy+=gID;
  //     sem_wait(&toyMut);
  //     toy[createdToy-1]++;
  //     cout << "gnome" << gID+1 << "(): Skończyłem produkcję zabawki (" << createdToy << ").\n" << buffor();
  //     bool enoughToys = (toy[0] >= 3 && toy[1] >= 3 && toy[2] >= 3);
  //
  //     if (enoughToys && santaSleeping) {
  //       cout << "gnome" << gID+1 << "(): Budzę Mikołaja.\n";
  //       santaSleeping = false;
  //       sem_post(&santaSem);
  //     }
  //
  //     sem_post(&toyMut);
  //
  //     firstPartNotCreated = true;
  //     sem_post(&gnomeSem[blockedGnome]);
  //     sem_post(&gnomes);
  //   }
  // }
  pthread_exit(NULL);
}

void *service(void *sth) {
  // while (true) {
  //   sem_wait(&santaSem);
  //   sem_wait(&toyMut);
  //   cout << "santa(): Zabawki się uzbierały, wstaję do pracy...\n";
  //
  //   #ifdef SLEEP_ENABLED
  //     sleep(3);
  //   #endif
  //
  //   for (int i = 0; i < 3; i++)
  //     toy[i] -= 3;
  //
  //   cout << "santa(): Zabawki wysłane. Czas iść spać...\n" << buffor();
  //   santaSleeping = true;
  //   sem_post(&toyMut);
  // }
  pthread_exit(NULL);
}

int main( int argc, char * argv[] ) {

  pthread_t threads[argc-1];

  pthread_create(&threads[0], NULL, service, NULL);

  for (long i = 2; i < argc; i++) {
    pthread_create(&threads[i], NULL, requester, (void *) argv[i]);
  }

  // sem_init(&toyMut, 0, 1);  //mutex na buffory (wszystkie 3)
  // sem_init(&gnomes, 0, 1);
  // sem_init(&santaSem, 0, 0);
  // sem_init(&gnomeSem[0] ,0, 0);
  // sem_init(&gnomeSem[1] ,0, 0);
  // sem_init(&gnomeSem[2] ,0, 0);
  //
  //
  //
  //

  //
  //
  // for (int i = 0; i < 4; i++)
  //   pthread_join(threads[i], NULL);

  return 0;
}
