/*Dynamically allocating the Major and Minor number*/
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
 
dev_t dev = 0;

/*Module Init function*/

static int __init char1_init(void)
{
        /*Allocating Major number*/
        alloc_chrdev_region(&dev, 0, 1, "CharacterDevice1");
  
        /*if((alloc_chrdev_region(&dev, 0, 1, "CharacterDevice1")) <0){
                printk(KERN_INFO "Cannot allocate major number for device 1\n");
                return -1;
        }*/
        
        printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
        printk(KERN_INFO "Kernel Module Inserted Successfully...\n");
        return 0;
        
}

/*Module exit function*/

static void __exit char1_exit(void)
{
        unregister_chrdev_region(dev, 1);
        printk(KERN_INFO "Kernel Module Removed Successfully...\n");
}
 
module_init(char1_init);
module_exit(char1_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC");
MODULE_DESCRIPTION("Dynamically allocating the Major and Minor number");
MODULE_VERSION("1.1");
