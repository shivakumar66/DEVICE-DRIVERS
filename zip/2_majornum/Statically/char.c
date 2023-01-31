/*STATICALLY ALLOCATING MAJOR NUMBER AND MINOR NUMER(Device Number)*/
/*LANANA*/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/types.h>
#include<linux/kdev_t.h>

//creating the dev with our custom major and minor number
dev_t dev = MKDEV(100,0);

/* Module Init function*/

static int __init char_init(void)
{
    register_chrdev_region(dev, 1, "characterDevice");
    printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
    printk(KERN_INFO "Kernel Module Inserted Successfully...\n");
    return 0;
}

/*Module exit function*/

static void __exit char_exit(void)
{
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "Kernel Module Removed Successfully...\n");
}
 
module_init(char_init);
module_exit(char_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC");
MODULE_DESCRIPTION("STATICALLY ALLOCATING MAJOR NUMBER AND MINOR NUMER");

