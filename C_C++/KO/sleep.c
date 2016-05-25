#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/cred.h>

#include <asm/uaccess.h>

#define MESSAGE_LENGTH 80
static char Message[MESSAGE_LENGTH];

static struct proc_dir_entry* proc_file_entry;
#define PROC_FILE_NAME "sleep"

static ssize_t module_output(struct file* file, char* buf, size_t len, loff_t* offset)
{
	static int finished = 0;
	int i;
	char message[MESSAGE_LENGTH+30];
	if(finished)
	{
		finished = 0;
		return 0;
	}

	sprintf(message, "Last input:%s\n", Message);
	for(i=0; i<len && message[i]; i++)
	{
		put_user(message[i], buf+i);
	}

	finished = 1;
	return i;
}

static ssize_t module_input(struct file* file, const char* buf, size_t len, loff_t* offset)
{
	int i;
	for(i=0; i<MESSAGE_LENGTH-1 && i<len; i++)
		get_user(Message[i], buf+i);
	Message[i] = '\0';

	return i;
}

int Already_Open = 0;
DECLARE_WAIT_QUEUE_HEAD(WaitQ);

static int module_permission(struct inode* inode, int op)
{
	if(op == 4 || (op == 2 && current_euid().val == 0))
	{
		return 0;
	}

	return -EACCES;
}

static struct inode_operations iops = {
	.permission = module_permission
};

static int module_open(struct inode* inode, struct file* file)
{
	if((file->f_flags & O_NONBLOCK) && Already_Open)
	{
		return -EAGAIN;
	}

	try_module_get(THIS_MODULE);
	inode->i_op = &iops;

	while(Already_Open)
	{
		int i, is_sig = 0;
		wait_event_interruptible(WaitQ, !Already_Open);
		for(i=0; i<_NSIG_WORDS && !is_sig; i++)
			is_sig = current->pending.signal.sig[i] & ~current->blocked.sig[i];

		if(is_sig)
		{
			module_put(THIS_MODULE);
			return -EINTR;
		}
	}

	Already_Open = 1;
	return 0;
}

int module_close(struct inode* inode, struct file* file)
{
	Already_Open = 0;
	wake_up(&WaitQ);
	module_put(THIS_MODULE);
	return 0;
}



static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = module_output,
	.write = module_input,
	.open = module_open,
	.release = module_close
};


static int __init my_init(void)
{
	int rv = 0;
	proc_file_entry = proc_create(PROC_FILE_NAME, 0644, NULL, &fops);
	if(proc_file_entry == NULL)
	{
		rv = -ENOMEM;
		remove_proc_entry(PROC_FILE_NAME, NULL);
		printk(KERN_INFO "Error: Could not initialize the /proc/sleep\n");
	}
	return rv;
}

static void __exit my_exit(void)
{
	remove_proc_entry(PROC_FILE_NAME, NULL);
}

module_init(my_init);
module_exit(my_exit);

