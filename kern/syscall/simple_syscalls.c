//simple system calls for assignment 2
//Stephen Boyd

#include <types.h>
#include <kern/errno.h>
#include <kern/syscall.h>
#include <mips/trapframe.h>
#include <current.h>
#include <copyinout.h>
#include <syscall.h>
#include <lib.h>
#include <kern/unistd.h>
#include <thread.h>

void sys__exit(int code) {
  thread_exit();
}

int sys_helloworld(void){
  kprintf("\nheeeeeey world\n");
  return 0;
}
