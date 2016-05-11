#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void)
{
	printk(KERN_INFO "Hello World!\n");

	return 0;
}

void clean_module(void)
{
	printk(KERN_INFO "GoodBye World!\n");
}
