#include <linux/kernel.h>
#include <linux/module.h>

static void __exit test_exit(void)
{
	printk(KERN_INFO "test exit ok!\n");
}

module_exit(test_exit);

