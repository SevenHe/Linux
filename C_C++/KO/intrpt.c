#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>
#include <linux/irqreturn.h> 	/* for irqreturn_t */
#include <linux/sched.h>
#include <asm/io.h>

#define MY_WORK_QUEUE_NAME "WQsched.c"

/* find from the /dev/... */
static int kbd_dev_id = 9;

static struct workqueue_struct* my_workqueue;
struct my_work {
	unsigned char scancode;
	struct work_struct work;
};

static void get_char(struct work_struct* tp)
{
	/* container_of(ptr, type, member) = ({\
	// const typeof(((type*)0)->member)* _mptr = ptr;\
	// (type*)((char*)_mptr - offsetof(type, member)); }); // this is the return value.
	// offsetof(type, member) ((size_t) & ((type*)0)->member )
	*/
	struct my_work* mp = container_of(tp, struct my_work, work);
	printk("Scan Code %c %s.\n", 
			*((char*)&(mp->scancode)),
			*((char*)&(mp->scancode)) & 0x80 ? "Released" : "Pressed");
}

irqreturn_t irq_handler(int irq, void* dev_id)
{
	static int initialised = 0;
	static struct my_work task;
	unsigned char status;

	/* 0x64 is the status registrator, 0x60 is the data registrator. */
	/* read from keyboard */
	status = inb(0x64);
	task.scancode = inb(0x60);

	printk(KERN_INFO "Get into the irq handler: scancode-%c\n", task.scancode);

	if(initialised == 0)
	{
		INIT_WORK(&task.work, get_char);
		initialised = 1;
	}
	else
		schedule_work(&task.work);

	queue_work(my_workqueue, &task.work);

	return IRQ_HANDLED;
}

static int __init my_init(void)
{
	my_workqueue = create_workqueue(MY_WORK_QUEUE_NAME);

	/* we need to reboot! */
	free_irq(1, (void*)(&kbd_dev_id));
	
	printk(KERN_INFO "hijack the keyboard irq!\n");

	return request_irq(1,		/* The IRQ Number */
				irq_handler,	/* the handler */
				IRQF_SHARED, "test_keyboard_irq_handler",
				(void*)(irq_handler));
}

static void __exit my_exit(void)
{
	/* reinstate */
	free_irq(1, (void*)(&kbd_dev_id));
	destroy_workqueue(my_workqueue);

	printk(KERN_INFO "irq hijack is removed.\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");


