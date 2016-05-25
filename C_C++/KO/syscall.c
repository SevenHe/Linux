#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>

#include <linux/sched.h>
#include <asm/uaccess.h>

extern void* sys_call_table[];

static int uid;
module_param(uid, int, 0644);

asmlinkage int (*original_call)(const char*, int, int);

asmlinkage int our_sys_open(const char* filename, int flags, int mode)
{
	int i = 0;
	char ch;
	if(uid == current->uid)
	{
		printk("Opened file by %d:", uid);
		do
		{
			get_user(ch, filename+i);
			i++;
			printk("%c", ch);
		}while(ch != 0);
		printk("\n");

	}
	return original_call(filename, flags, mode);
}

static int __init my_init_module(void)
{
	printk(KERN_ALERT "I'm dangerous. I hope you did a ");
	printk(KERN_ALERT "sync before you insmod'ed me.\n");
	printk(KERN_ALERT "My counterpart, cleanup_module(), is even");
	printk(KERN_ALERT "more dangerous. If\n");
	printk(KERN_ALERT "you value your file system, it will ");
	printk(KERN_ALERT "be \"sync; rmmod\" \n");
	printk(KERN_ALERT "when you remove this module.\n");

	original_call = sys_call_table[_NR_open];
	sys_call_table[_NR_open] = our_sys_open;

	return 0;
}

static void __exit my_exit_module(void)
{
	if (sys_call_table[__NR_open] != our_sys_open) {
		printk(KERN_ALERT "Somebody else also played with the ");
		printk(KERN_ALERT "open system call\n");
		printk(KERN_ALERT "The system may be left in ");
		printk(KERN_ALERT "an unstable state.\n");
	}

	sys_call_table[_NR_open] = original_call;
}

module_init(my_init_module);
module_exit(my_exit_module);

