#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

#define SUCCESS 0

MODULE_AUTHOR("Seven");
MODULE_LICENSE("GPL");

static int __init test_init(void)
{
	int ma, mb;
	int* tmp = &ma;

	ma = 1;
	mb = 2;
	printk(KERN_INFO "Init my module!\n");
	printk(KERN_INFO "a=%p, b=%p\n", tmp, &mb);
	// macro, so not used the value!!
	assign(tmp, &mb);
	printk(KERN_INFO "a=%p, b=%p\n", tmp, &mb);
	return SUCCESS;
}

static void __exit test_exit(void)
{
	printk(KERN_INFO "exit my module!\n");
}

module_init(test_init);
module_exit(test_exit);
