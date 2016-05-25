#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include <linux/interrupt.h>

#include <asm/uaccess.h>
struct proc_dir_entry* my_proc_entry;
#define PROC_ENTRY_NAME "sched"
#define MY_WORK_QUEUE_NAME "WQsched.c"

static int TimerIntrpt = 0;
static void intrpt_routine(struct work_struct*);
static int die = 0;

static struct workqueue_struct* my_workqueue;
static struct delayed_work Task;
static DECLARE_DELAYED_WORK(Task, intrpt_routine);

static void intrpt_routine(struct work_struct* irrelevant)
{
	TimerIntrpt ++;
	printk(KERN_INFO "Get into the delayed_work: die = %d\n", die);
	if(die == 0)
		queue_delayed_work(my_workqueue, &Task, 100);
}

static ssize_t procfile_read(struct file* file, char* buffer, size_t buf_len, loff_t* offset)
{
	int len;	 
	static char my_buffer[80];
	static int count = 1;
	if(*offset > 0)
	{
		return 0;
	}
	len = sprintf(my_buffer, "Time called %d times so far\n", TimerIntrpt);
	if(count < 5)
		printk(KERN_INFO "Get the %d times read\n", count);
	count ++;
	// every 100 jiffies will do this, so dangerous!
	//copy_to_user(buffer, my_buffer, len);
	/* Tell the buffer where is 'I'*/
	offset = (loff_t*)my_buffer;
	return len;
}

static struct file_operations proc_fops = {
	.owner = THIS_MODULE,
	.read = procfile_read
};

static int __init my_sched_init(void)
{
	my_proc_entry = proc_create(PROC_ENTRY_NAME, 0644, NULL, &proc_fops);
	if(my_proc_entry == NULL)
	{
		remove_proc_entry(PROC_ENTRY_NAME, NULL);
		printk(KERN_INFO "Error: Could not initialize the /proc/%s\n", PROC_ENTRY_NAME);
		return -ENOMEM;
	}

	my_workqueue = create_workqueue(MY_WORK_QUEUE_NAME);
	queue_delayed_work(my_workqueue, &Task, 100);
	printk(KERN_INFO "/proc/%s created \n", PROC_ENTRY_NAME);
	
	return 0;
}

static void __exit my_sched_exit(void)
{
	remove_proc_entry(PROC_ENTRY_NAME, NULL);
	printk(KERN_INFO "/proc/%s removed\n", PROC_ENTRY_NAME);
	
	die = 1;
	cancel_delayed_work(&Task);
	flush_workqueue(my_workqueue);
	destroy_workqueue(my_workqueue);
}

module_init(my_sched_init);
module_exit(my_sched_exit);
MODULE_AUTHOR("SEVEN");
MODULE_LICENSE("GPL");

	
		

