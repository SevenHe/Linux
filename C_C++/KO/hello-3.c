#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

static int hello3_data__intdata = 3;

static int __init hello3_init(void)
{
	printk(KERN_INFO "Hello World3!\n");

	return 0;
}

static void __exit hello3_exit(void)
{
	printk(KERN_INFO "GoodBye World3!\n");
}

module_init(hello3_init);
module_exit(hello3_exit);
