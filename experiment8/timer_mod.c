#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("XAUT");
MODULE_DESCRIPTION("THIS IS MY FIRST TIMER");
void my_timer_function(unsigned long data)
{
    printk(KERN_ALERT "after 5 seconds,time come");
}
static int func_init(void)
{
    static struct timer_list my_timer;
    init_timer(&my_timer);
    my_timer.expires = jiffies+5000;
    my_timer.data = 0;
    my_timer.function = my_timer_function;
    add_timer(&my_timer);
    printk(KERN_ALERT "timer_mod initing... ok\n");
    return 0 ;
}
static void func_exit(void)
{
    printk(KERN_ALERT "timer_mod exiting...ok");
}
module_init(func_init);
module_exit(func_exit);
