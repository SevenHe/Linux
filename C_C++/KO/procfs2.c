#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/seq_file.h>

#define PROC_NAME "Test"

MODULE_AUTHOR("Seven");
MODULE_LICENSE("GPL");

static void* seq_start(struct seq_file* s, loff_t* pos)
{
	static unsigned long counter = 0;
	if(*pos == 0)
	{
		return &counter;
	}
	else
	{
		*pos = 0;
		return NULL;
	}
}

static void* seq_next(struct seq_file* s, void* v, loff_t* pos)
{
	unsigned long* tmp_v = (unsigned long*)v;
	(*tmp_v) ++;
	(*pos) ++;
	return NULL;
}

/* a function name will be treated as type* ? */
static void seq_stop(struct seq_file* s, void* v)
{
	/* Nothing to do */
}

static int seq_show(struct seq_file* s, void* v)
{
	loff_t* spos = (loff_t*)v;
	seq_printf(s, "%Ld\n", *spos);
	return 0;
}

static struct seq_operations my_seq_ops = {
	.start = seq_start,
	.next = seq_next,
	.stop = seq_stop,
	.show = seq_show,
};

static int my_open(struct inode* inode, struct file* file)
{
	return seq_open(file, &my_seq_ops);
}

static struct file_operations my_file_ops = {
	.owner = THIS_MODULE,
	.open = my_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = seq_release,
};

static int __init my_init_module(void)
{
	struct proc_dir_entry* entry;
	entry = proc_create(PROC_NAME, 0, NULL, &my_file_ops);
	if(!entry)
	{
		return -EFAULT;
	}
	return 0;
}

static void __exit my_cleanup_module(void)
{
	remove_proc_entry(PROC_NAME, NULL);
	printk(KERN_INFO "/proc/%s has been cleaned up!\n", PROC_NAME);
}

module_init(my_init_module);
module_exit(my_cleanup_module);
