#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>
#include <test.h>
#include <stephen.h>
//Stephen Boyd

static struct semaphore *tsem = NULL;


static
void
init_sem(void)
{
  if (tsem==NULL) {
    tsem = sem_create("tsem", 1);
    if (tsem == NULL) {
      panic("threadtest: sem create failed\n");
    }
  }
}


void wut(void){
  kprintf("wut ");
  V(tsem);
}

static
void
runtt4(int num_threads)
{
	char name[16];
	int i, result;
	for (i=0; i<num_threads; i++) {
		result = thread_fork(name, NULL,
				     wut,
				     NULL, i);
		if (result) {
			panic("threadtest: thread_fork failed %s)\n", 
			      strerror(result));
		}
	}
	for (i=0; i<num_threads; i++) {
		P(tsem);
	}
}

int
threadtest4(int nargs, char **args)
{
  int num_threads = atoi(args[1]);
  if (nargs==2) {
    init_sem();
    kprintf("Starting thread test 4...\n");
    runtt4(num_threads);	
	  kprintf("\nThread test 4 done. \n");
  } else {
    kprintf("\nEnter exactly one integer argument to use this test\n");
  }
	return 0;
}




int counter = 0;

void countprinter(void * unusedpointer, unsigned long num_increment){
  (void) unusedpointer;
  unsigned long i;
  for (i=0; i<num_increment; i++){
    counter += 1;
  }
  kprintf("\n %d \n", counter);
  V(tsem);
}

static
void
rununsafe(int num_threads, int num_increment)
{
	char name[16];
	int i, result;
	for (i=0; i<num_threads; i++) {
		result = thread_fork(name, NULL,
				     countprinter,
				     NULL, num_increment);
		if (result) {
			panic("threadtest: thread_fork failed %s)\n", 
			      strerror(result));
		}
	}
  counter = 0;
	for (i=0; i<num_threads; i++) {
		P(tsem);
	}
}

int
unsafethreadcounter(int nargs, char **args)
{
  int num_threads = atoi(args[1]);
  int num_increment = atoi(args[2]);
  if (nargs==3) {
    init_sem();
    kprintf("Starting unsafe thread test...\n");
    rununsafe(num_threads, num_increment);	
	  kprintf("\nUnsafe thread test done. \n");
  } else {
    kprintf("\nEnter exactly two integer arguments to use this test\n");
  }
  kprintf("\nThe final number is: %d\n", counter);
	return 0;
}




void safecountprinter(void * unusedpointer, unsigned long num_increment){
  (void) unusedpointer;
  unsigned long i;
  P(tsem);
  for (i=0; i<num_increment; i++){
//    P(tsem);
    counter += 1;
//    V(tsem);
  }
  kprintf("\n %d \n", counter);
  V(tsem);
}

static
void
runsafe(int num_threads, int num_increment)
{
	char name[16];
	int i, result;
	for (i=0; i<num_threads; i++) {
		result = thread_fork(name, NULL,
				     safecountprinter,
				     NULL, num_increment);
		if (result) {
			panic("threadtest: thread_fork failed %s)\n", 
			      strerror(result));
		}
	}
  counter = 0;
	for (i=0; i<num_threads; i++) {
		P(tsem);
	}
}

int
safethreadcounter(int nargs, char **args)
{
  int num_threads = atoi(args[1]);
  int num_increment = atoi(args[2]);
  if (nargs==3) {
    init_sem();
    kprintf("Starting safe thread test...\n");
    rununsafe(num_threads, num_increment);	
	  kprintf("\nsafe thread test done. \n");
  } else {
    kprintf("\nEnter exactly two integer arguments to use this test\n");
  }
  kprintf("\nThe final number is: %d\n", counter);
	return 0;
}


