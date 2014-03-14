//simple system calls for assignment 2
//Stephen Boyd

#include <types.h>
#include <copyinout.h>
#include <syscall.h>
#include <lib.h>

int sys_helloworld(void){
  kprintf("\nheeeeeey world\n");
  return 0;
}
