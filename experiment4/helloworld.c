#ifndef MODULE
	#define MODULE
#endif

#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("xautlinux@mail.com");
MODULE_DESCRIPTION("This is a test module");

static int N=3;
module_param(N,int,0644);

int my_print(int n)
{
	printk(KERN_ALERT"in helloworld.ko: parm N is:%d\n",n);
	return 0;

}
EXPORT_SYMBOL(my_print);
static int init_hello(void)
{
	printk(KERN_ALERT"in helloworld.ko: Hello,Linux world!\nparam is:%d\n",N);
	return 0;
}
static void exit_hello(void)
{
	printk(KERN_ALERT"in helloworld.ko: Goodbye,Cruel world!\n");
	
}
module_init(init_hello);
module_exit(exit_hello);



