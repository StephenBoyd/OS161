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

#define KBUF_MAX 256

void sys__exit(int code) {
  thread_exit();
}

int sys_helloworld(void){
  kprintf("\nheeeeeey world\n");
  return 0;
}

int sys_printint(int value){
  kprintf("%d\n", value);
  return 0;
}

int sys_printstring(char * string, size_t length){
  kprintf("%s\n", string);
  return 0;
}

int sys_write(int fd, const void* buf, size_t nbytes){
  //if (fd != 1) return EBADF;
  char kbuf[KBUF_MAX];
  if (nbytes >= KBUF_MAX) return EFAULT;
  copyin(buf, kbuf, nbytes);
  kbuf[nbytes+1] = 0;
  kprintf(kbuf);
  return 0;
}
