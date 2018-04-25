#include <linux/module.h>
extern int my_print(int n);
MODULE_LICENSE("GPL");
static int init_hello2(void)
{
	request_module("helloworld");
	printk(KERN_ALERT "in hello2.ko: request helloworld.ko\n");
	my_print(5);
	return 0;
}
module_init(init_hello2);
void cleaup_module(void)
{
	printk(KERN_ALERT "in hello.ko:leaving...........successed!\n");
}

