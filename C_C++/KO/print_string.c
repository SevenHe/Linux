#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/version.h>
#include <linux/tty.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Seven");

static void print_string(char* str)
{
	struct tty_struct* my_tty;

#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,5))
	my_tty = current->tty;
#else
	my_tty = current->signal->tty;
#endif
	if(my_tty != NULL)
	{
		my_tty->driver->ops->write(my_tty, str, strlen(str));
		// fill the end
		my_tty->driver->ops->write(my_tty, "\015\012", 2);
	}
}

static int __init ps_init(void)
{
	print_string("The module has been inserted. Hello World!");
	return 0;
}

static void __exit ps_exit(void)
{
	print_string("The module has been removed! Farewell World!");
}

module_init(ps_init);
module_exit(ps_exit);

