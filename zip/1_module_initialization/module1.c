/*Module_Initialization & De-Initialization*/
/*we will find information about header files in the path as /lib/modules/5.15.0-56-generic/build/include/linux$*/
/*we will find information about header files in the path as /lib/modules/$(uname -r)/build/include/linux$*/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
 
/*Module Init function*/

static int __init module1_init(void)
{
    printk(KERN_INFO "Welcome To CDAC-HYDERABAD\n");
    printk(KERN_INFO "Device Driver Session Started\n");
    printk(KERN_INFO "Check prints on screen using dmesg command\n");
    printk(KERN_INFO "Kernel Module Inserted Successfully...\n");
    return 0;
}

/*Module Exit function*/

static void __exit module1_exit(void)
{
	printk(KERN_INFO "Practice On Module initialization Concepts\n");
    	printk(KERN_INFO "Kernel Module Removed Successfully...\n");
}
 
module_init(module1_init);
module_exit(module1_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("CDAC");
MODULE_DESCRIPTION("Learning Dynamic Module insertion and deletion");
MODULE_VERSION("2.0");
