/*Manually Creating Device File*/
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
 
dev_t dev = 0;

/*Module Init function*/
static int __init char2_init(void)
{
        /*Allocating Major number*/
        alloc_chrdev_region(&dev, 0, 1, "CharacterDevice2");
        printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
        printk(KERN_INFO "Kernel Module Inserted Successfully....\n");
        return 0;
}

/*Module exit function*/
static void __exit char2_exit(void)
{
        unregister_chrdev_region(dev, 1);
        printk(KERN_INFO "Kernel Module Removed Successfully...\n");
}
 
module_init(char2_init);
module_exit(char2_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC");
MODULE_DESCRIPTION("Manually Creating Device File using mknod");

//printk(KERN_INFO "Manually Create Device using mknod -m <permissions> <name> <device type> <major> <minor> :EX:- sudo mknod -m 666 /dev/CDAC_device c 236 0");
        //printk(KERN_INFO "EX:- sudo mknod -m 666 /dev/CDAC_device c 236 0");
        //printk(KERN_INFO "  229  ls -l /dev
  //230  ls -l /dev | grep "char2_device"
  //231  sudo rm /dev/char2_device
  //232  ls -l /dev | grep "char2_device"
  //233  ls -l /dev
//");

