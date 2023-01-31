/*FILE_OPERATIONS ON HOST MACHINE Using "echo" and "cat" command*/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include<linux/slab.h>
#include <linux/err.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/uaccess.h>
#include<linux/wait.h>
#include<linux/kthread.h>
#include<linux/types.h>

dev_t dev = 0;
static struct class *dev_class;
static struct cdev file_cdev;
static struct task_struct *wait_thread;                               // *kernel_buffer
int wait_queue_flag = 0;
#define MEM_SIZE 1024  
uint32_t read_count = 0;
uint8_t *kernel_buffer;   

DECLARE_WAIT_QUEUE_HEAD(wq_file);

/*Function Prototypes(we can find function protoype by using below command) */
/*gedit /lib/modules/$(uname -r)/build/include/linux/fs.h*/
static int      __init file_oper_init(void);
static void     __exit file_oper_exit(void);
static int      file_open(struct inode *inode, struct file *file);
static int      file_release(struct inode *inode, struct file *file);
static ssize_t  file_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t  file_write(struct file *filp, const char *buf, size_t len, loff_t * off);

static struct file_operations fops =
{
    .owner      = THIS_MODULE,
    .read       = file_read,
    .write      = file_write,
    .open       = file_open,
    .release    = file_release,
};

/*wait function initialization THREAD */
static int wait_function(void *wf)
{
    while(1)
    {
        pr_info("waiting for event\n");
        wait_event_interruptible(wq_file,wait_queue_flag!=0);
        if(wait_queue_flag==2)
        {
            //pr_info("Event came  from read function\n");
            pr_info("Event came from read function %d\n",++read_count);
            return 0;
        }
        if(wait_queue_flag==1)
        {
            //pr_info("Event came  from read function\n");
            pr_info("Event came from write function %d\n",++read_count);
            wait_queue_flag = 0;
            return 0;
        }
        //read_count = 0;
        
    }
    do_exit(0);
    //wait_queue_flag = 0;
    return 0;
}

/*This function will be called when we open the Device file*/

static int file_open(struct inode *inode, struct file *file)
{
        pr_info("Driver Open Function Called...!!!\n");
        return 0;
}

/*This function will be called when we close the Device file*/

static int file_release(struct inode *inode, struct file *file)
{
        pr_info("Driver Release Function Called...!!!\n");
        return 0;
}

/* This function will be called when we read the Device file*/

static ssize_t file_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
        pr_info("Driver Read Function Called...!!!\n");
        wait_queue_flag = 1;
        wake_up_interruptible(&wq_file);
        return 0;
}

/*This function will be called when we write the Device file*/

static ssize_t file_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
        pr_info("Driver Write Function Called...!!!\n");
        wait_queue_flag = 3;
        pr_info("falg value ...!!!%d\n",wait_queue_flag);
        wake_up_interruptible(&wq_file);
        return len;
}

/*Module Init function*/
static int __init file_oper_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "file_Dev")) <0)
        {
                pr_err("Cannot allocate major number\n");
                return -1;
        }
        pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));

        /*Creating cdev structure*/
        cdev_init(&file_cdev,&fops);
	file_cdev.owner = THIS_MODULE;
	file_cdev.ops = &fops;

        /*Adding character device to the system*/
        if((cdev_add(&file_cdev,dev,1)) < 0){
            pr_err("Cannot add the device to the system\n");
            goto r_class;
        }

        /*Creating struct class*/
        if(IS_ERR(dev_class = class_create(THIS_MODULE,"file_class"))==NULL){
            pr_err("Cannot create the struct class\n");
            goto r_class;
        }

        /*Creating device*/
        if(IS_ERR(device_create(dev_class,NULL,dev,NULL,"file_device"))==NULL){
            pr_err("Cannot create the Device 1\n");
            goto r_device;
        }

        // Creating Physical Memory
    if((kernel_buffer = kmalloc(MEM_SIZE,GFP_KERNEL)) == 0) {
        pr_err("Can not allocate memory in Kernel\n");
        goto r_device;
    }

	/*Creating thread*/
        wait_thread = kthread_create(wait_function,NULL,"Wait thread");
        if(wait_thread)
        {
            pr_info("Thread created successfully\n");
            wake_up_process(wait_thread);
        }
        else
        {
            pr_info("Thread creation failed\n");
        }
        pr_info("Device Driver Insert...Done!!!\n");


      return 0;

r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        return -1;
}

/*Module exit function*/
static void __exit file_oper_exit(void)
{
        wait_queue_flag=2;
     	wake_up_interruptible(&wq_file);
	device_destroy(dev_class,dev);

	class_destroy(dev_class);
       	cdev_del(&file_cdev);
        unregister_chrdev_region(dev, 1);
        pr_info("Device Driver Remove...Done!!!\n");
}

module_init(file_oper_init);
module_exit(file_oper_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC");
MODULE_DESCRIPTION("File Operations");
