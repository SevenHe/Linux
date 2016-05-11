#include <linux/kernel.h>	/* FOR KERNEL MACROS */
#include <linux/module.h>	/* A MODULE */

static int __init test_init(void)
{
	printk(KERN_INFO "test separated files start!\n");
	return 0;
}

module_init(test_init);

