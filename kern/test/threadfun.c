#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>
#include <test.h>


static struct semaphore *tsem = NULL;

static
void
init_sem(void)
{
  if (tsem==NULL) {
    tsem = sem_create("tsem", 0);
    if (tsem == NULL) {
      panic("threadtest: sem create failed\n");
    }
  }
}

void wut(){
  kprintf("wut ");
  V(tsem);
}

static
void
funthreads(int num_threads)
{
	char name[16];
	int i, result;

	for (i=0; i<num_threads; i++) {
		snprintf(name, sizeof(name), "threadtest%d", i);
		result = thread_fork(name, NULL,
				     wut, // figure this out!
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
    funthreads(num_threads);	
	  kprintf("\nThread test 4 done. \n");
  } else {
    kprintf("Enter exactly one integer argument to use this test");
  }
	return 0;
}
