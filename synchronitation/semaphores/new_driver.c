#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>                 //kmalloc()
#include <linux/uaccess.h>              //copy_to/from_user()
#include <linux/err.h>
#include<linux/semaphore.h>
 
  dev_t dev;
//static struct class *dev_class;
static struct cdev driver2_cdev;
struct semaphore my_sema;
int op_result=5;

//static int      __init newdriver_init(void);
//static void     __exit newdriver_exit(void);
static int      file_open(struct inode *inode, struct file *file);
static int      file_release(struct inode *inode, struct file *file);
static ssize_t  file_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t  file_write(struct file *filp, const char *buf, size_t len, loff_t * off);

static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .open           = file_open,
        .release        = file_release,
        .read           = file_read,
        .write          = file_write,
};

/*This function will be called when we open the Device file*/

static int file_open(struct inode *inode, struct file *file)
{
        printk("Device File Opened...!!!\n");
        return 0;
}

/*This function will be called when we close the Device file*/

static int file_release(struct inode *inode, struct file *file)
{
        printk("Device File Closed...!!!\n");
        return 0;
}

/* This function will be called when we read the Device file*/

static ssize_t file_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    printk("Driver Read Function Called...!!!\n");
    unsigned long result;
     ssize_t retval;
     printk("application and functionality");
     printk("before sending the result into the signal");
     result=copy_to_user((char*)buf,(char*)&op_result,sizeof(op_result));
     if(result>=0){ 
     printk("data successfullt created\n");
     retval = sizeof(op_result);
     up(&my_sema);
     }
     else{
        printk("errroe in data reading");
        return -1;

     }
        return retval;
}

/*This function will be called when we write the Device file*/

static ssize_t file_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
        printk("Driver Write Function Called...!!!\n");
        down(&my_sema); 
        int kernel_buffer[2];
        int num1,num2;
        unsigned long result;
        ssize_t retval;

            printk("write system call.....\n");


        //Copy the data to kernel space from the user-space
        result= copy_from_user((char *)kernel_buffer,buf,len);

        if(result>=0)
        {
            printk("Data write successful ..\n");
            num1=kernel_buffer[0];
            num2=kernel_buffer[1];
            op_result=num1+num2;
            printk("The result of sum of these %d and %d two numbers are %d/n",num1,num2,op_result);
            retval=len;
           
        }
         return retval;
}

static int __init vishal_init(void)
{

    if((alloc_chrdev_region(&dev, 0, 3, "newdriver_Dev"))<0)
    {
        printk("Cannot allocate major number\n");
        return -1;
    }
    printk("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));

     /*Creating cdev structure*/
    cdev_init(&driver2_cdev,&fops);

     /*Adding character device to the system*/
        if((cdev_add(&driver2_cdev,dev,3)) < 0){
        printk("Cannot add the device to the system\n");
        unregister_chrdev_region(dev,3);
        return -1;   
        }
    printk("Charecter file added succesfully\n.........Device Driver inserted successfully\n");
    sema_init(&my_sema,1);

       return 0;
 


}

static void     __exit vishal_exit(void)
{
    cdev_del(&driver2_cdev);
    unregister_chrdev_region(dev, 3);
    printk("Device Driver Remove...Done!!!\n");
}


module_init(vishal_init);
module_exit(vishal_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("vishal");



