#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/workqueue.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xautlinux@gmail.com");
MODULE_DESCRIPTION("This is a test module");
static struct workqueue_struct *queue = NULL;
static struct work_struct work;
static struct delayed_work *dwork;
/*work handle*/
void work_handle(struct work_struct *work)
{
    printk(KERN_ALERT "after 5 seconds,xaut's work running......\n");
}
static int init_workqueue(void)
{
    queue = create_workqueue("xaut_queue_events");
    printk(KERN_ALERT "workqueue.mod loading......OK\n");
    if(queue == NULL)
    {
        printk(KERN_ALERT "create xaut's workqueue error\n");
        return -1;
    }
    printk("create xuat's workqueue OK\n");
    INIT_WORK(&work,work_handle);
    dwork = to_delayed_work(&work);
    queue_delayed_work(queue,dwork,5000);
    return 0;
}
static void exit_workqueue(void)
{
    flush_workqueue(queue);
    cancel_delayed_work(dwork);
    destroy_workqueue(queue);
    printk(KERN_ALERT "xuat's workqueue unloading......OK\n");
}
module_init(init_workqueue);
module_exit(exit_workqueue);
