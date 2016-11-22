# Systemy Operacyjne - Pracownia 2

## Treść zadania

######Disk scheduler

In this part, you will write a concurrent program to issue and service disk requests.  We will provide a working thread library (thread.o) for you to use while testing your disk scheduler. 

The disk scheduler in an operating system gets and schedules disk I/Os for multiple threads.  Threads issue disk requests by queueing them at the disk scheduler.  The disk scheduler queue can contain at most a specified number of requests (max_disk_queue); threads must wait if the queue is full.

Your program should start by creating a specified number of requester threads to issue disk requests and one thread to service disk requests.  Each requester thread should issue a series of requests for disk tracks (specified in its input file).  Each request is synchronous; a requester thread must wait until the servicing thread finishes handling its last request before issuing its next request.  A requester thread finishes after all the requests in its input file have been serviced.

Requests in the disk queue are NOT serviced in FIFO order.  Instead, the service thread handles disk requests in SSTF order (shortest seek time first). That is, the next request it services is the request that is closest to its current track.  The disk is initialized with its current track as 0.

Keep the disk queue as full as possible to minimize average seek distance. That is, your service thread should only handle a request when the disk queue has the largest possible number of requests.  This gives the service thread the largest number of requests to choose from.  Note that the "largest number of requests" varies depending on how many request threads are still active. When at least max_disk_queue requester threads are alive, the largest possible number of requests in the queue is max_disk_queue.  When fewer than max_disk_queue requester threads are alive, the largest number of requests in the queue is equal to the number of living requester threads.  You will probably want to maintain the number of living requester threads as shared state.

**1 Input**

Your program will be called with several command-line arguments.  The first argument specifies the maximum number of requests that the disk queue can hold.  The rest of the arguments specify a list of input files (one input file per requester).  I.e. the input file for requester r is argv[r+2], where 0 <= r < (number of requesters).  The number of threads making disk requests should be deduced from the number of input files specified.

The input file for each requester contains that requester's series of requests. Each line of the input file specifies the track number of the request (0 to 999).  You may assume that input files are formatted correctly.  Open each input file read-only (use ifstream rather than fstream).

**2 Output**

After issuing a request, a requester thread should call (note the space characters in the strings):  
*cout << "requester " << requester << " track " << track << endl;*  

A request is available to be serviced when the requester thread prints this line.

After servicing a request, the service thread should make the following call (note the space characters in the strings):  
*cout << "service requester " << requester << " track " << track << endl;*  

A request is considered to be completely handled when the service thread prints this line.

Your program should not generate any other output.

Note that the console is shared between the different threads.  Hence the couts in your program must be protected by a monitor lock to prevent interleaving output from multiple threads.

**3 Sample input/output**

Here is an example set of input files (disk.in0 - disk.in4).
```
disk.in0   disk.in1   disk.in2   disk.in3   disk.in4
--------   --------   --------   --------   --------
53         914        827        302        631
785        350        567        230        11
```

Here is one of several possible correct outputs from running the disk scheduler with the following command:
    disk 3 disk.in0 disk.in1 disk.in2 disk.in3 disk.in4

(The final line of the output is produced by the thread library, not the disk scheduler.)
```
-------------------------------------------------------------------------------
requester 0 track 53
requester 1 track 914
requester 2 track 827
service requester 0 track 53
requester 3 track 302
service requester 3 track 302
requester 4 track 631
service requester 4 track 631
requester 0 track 785
service requester 0 track 785
requester 3 track 230
service requester 2 track 827
requester 4 track 11
service requester 1 track 914
requester 2 track 567
service requester 2 track 567
requester 1 track 350
service requester 1 track 350
service requester 3 track 230
service requester 4 track 11
Thread library exiting.
-------------------------------------------------------------------------------
```

**4 Tips**

We will provide a working thread library (thread.o) for you to use while testing your disk scheduler.

## Wytyczne techniczne

1. Program powinien znaleźć się w osobnym repozytorium i powinien zawierać plik Makefile w katalogu głównym.
2. Program powinien być obsługiwany z poziomu polecenia make. Uruchomienie polecenia 'make' powinno służyć do kompilacji pod warunkiem zmian w pliku main.c(pp). Uruchomienie polecenia 'make run' powinno służyć do uruchomienia programu.
3. Program powinien być napisany w C lub C++ z użyciem bibilioteki pthreads (podpowiedź: gcc -lpthread)
4. Program powinien uruchamiać się na platformie Linux.
5. Repozytorium powinno zawierać plik .gitignore, za pomocą którego unikniesz umieszczania w repozytorium pliku binarnego.
6. Instrukcja kompilacji powinna zawierać flagi: -Wall, -Werror


