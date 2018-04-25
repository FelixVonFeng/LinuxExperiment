#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("XAUT");
MODULE_DESCRIPTION("THIS IS MY SECOND MODULE");
unsigned int test_major = 0;
int test_open(struct inode *inode,struct file *filp)
{
    try_module_get(&__this_module);
    printk(KERN_ALERT "chrdev_driver module is in open!\n");
    return 0;
}
int test_release(struct inode *inode,struct file *filp)
{
    module_put(THIS_MODULE);
    printk(KERN_ALERT "file is closed\n\n");
    return 0;
}
ssize_t test_read(struct file *filp,char __user *buf,size_t count,loff_t *offset)
{
    int i = 0,left;
    char ch = 'a';
    if(access_ok(VERIFY_READ,buf,count) == -EFAULT)
        return -EFAULT;
    for(left = count;left > 0;--left)
    {
        if(copy_to_user(&buf[i],&ch,1))
           {
               printk(KERN_ALERT "copy_to_user error\n");
               return 1;
           }
           ++i;
           ++ch;
    }
    return count;
}
static ssize_t test_write(struct file *filp,const char __user *buf,size_t count,loff_t *off)
{
    char *p = NULL;
    p = kmalloc(sizeof(char)*count,GFP_KERNEL);
    if(p == NULL)
    {
        printk(KERN_ALERT "kmalloc for p error\n");
        return 1;
    }
    if(copy_from_user(p,buf,count))
    {
        printk(KERN_ALERT "copy_from_user error\n");
        return 1;
    }
    printk(KERN_ALERT "%s\n",p);
    kfree(p);
    return 0;
}
struct file_operations test_fops={
    .owner = THIS_MODULE,
    .open = test_open,
    .release = test_release,
    .read = test_read,
    .write = test_write,
 };
static int func_init(void)
{
    int result;
    printk(KERN_ALERT "chrdev_driver module loading...\n");
    result = register_chrdev(test_major,"test",&test_fops);
    if(result < 0)
    {
        printk(KERN_ALERT "can't get major number\n");
        return result;
    }
    if(test_major == 0)
        test_major = result;
    return 0;
}
static void func_exit(void)
{
    printk(KERN_ALERT "\nchrdev_driver module unloading...\n");
    unregister_chrdev(test_major,"test");
}
module_init(func_init);
module_exit(func_exit);
