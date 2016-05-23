#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define PROCFS_NAME "HelloWorld"
#define PROCFS_MAX_SIZE 1024

static struct proc_dir_entry * Our_Proc_File;
static char procfs_buffer[PROCFS_MAX_SIZE];
static unsigned long procfs_buffer_size = 0;

static ssize_t procfile_read(struct file* file, char* buffer,
		size_t buf_length, loff_t* offset)
{
	int ret;
	printk(KERN_INFO "procfile_read (/proc/%s) called \n", PROCFS_NAME);
	if(*offset > 0)
	{
		ret = 0;
	}
	else
	{
		ret = sprintf(buffer, "HelloWorld\n");
	}
	return ret;
}

static ssize_t procfile_write(struct file* file, const char* buffer, size_t count,
			loff_t* data)
{
	procfs_buffer_size = count;
	if(procfs_buffer_size > PROCFS_MAX_SIZE)
	{
		procfs_buffer_size = PROCFS_MAX_SIZE;
	}
	if(copy_from_user(procfs_buffer, buffer, procfs_buffer_size))
	{
		return -EFAULT;
	}
	return procfs_buffer_size;
}

static struct file_operations proc_file_fops = {
	.owner = THIS_MODULE,
	.read = procfile_read,
	.write = procfile_write,
};

static int __init my_init_module(void)
{
	Our_Proc_File = proc_create(PROCFS_NAME, 0644, NULL, &proc_file_fops);
	if(Our_Proc_File == NULL)
	{
		remove_proc_entry(PROCFS_NAME, NULL);
		printk(KERN_ALERT "Error:Could not initialize /proc/%s\n", PROCFS_NAME);
		return -ENOMEM;
	}
	/* old version
	Our_Proc_File->read_proc = procfile_read;
	Our_Proc_File->write_proc = procfile_write;
	Our_Proc_File->owner = THIS_MODULE;
	Our_Proc_File->mode = S_IFREG|SIRUGO;
	Our_Proc_File->uid = 0;
	Our_Proc_File->gid = 0;
	Our_Proc_File->size = 37;
	*/
	printk(KERN_INFO "/proc/%s created\n", PROCFS_NAME);
	return 0;
}

static void __exit my_cleanup_module(void)
{
	remove_proc_entry(PROCFS_NAME, NULL);
	printk(KERN_INFO "/proc/%s removed\n", PROCFS_NAME);
}

module_init(my_init_module);
module_exit(my_cleanup_module);
