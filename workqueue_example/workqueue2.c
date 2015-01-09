#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>

MODULE_DESCRIPTION("workqueue example");
MODULE_AUTHOR("sumanth");
MODULE_LICENSE("GPL");

static atomic_t count = ATOMIC_INIT(0);
static struct workqueue_struct *kevent;
struct delayed_work my_work;

static void workqueue_handler(struct work_struct *data)
{
	atomic_inc(&count);
	printk(KERN_INFO " workqueue_handler count = %d", atomic_read(&count));
}


static int __init work_init(void)
{
	printk(KERN_INFO "workqueue module loaded");
	kevent = create_workqueue("noob");
	if(!kevent)
		return -ENOMEM;
	INIT_DELAYED_WORK(&my_work, workqueue_handler);
	queue_delayed_work(kevent, &my_work, 0); 
	
	return 0;
}

static void __exit work_exit(void)
{
	cancel_delayed_work(&my_work); 
	if(kevent)
		destroy_workqueue(kevent);
	return;
}

module_init(work_init);
module_exit(work_exit);

