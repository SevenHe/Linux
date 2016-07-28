#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

/** 
 * 系统调用号位于编译进linux内核中的syscall_64.tbl中,而非哪个包含的文件,这些头文件是自动生成的
 * 可以自己修改,但是内核中的才是实际的,而__NR_my_kern_func是给glib用的,而非用户调用系统调用的
 * 序号.用户间接调用syscall,使用的是table中的.
 */
#define __NR_my_kern_func 327

int main()
{
	long size;
	size = syscall(__NR_my_kern_func, 2);
	printf("stack size: %ld\n", size);
	return 0;
}
