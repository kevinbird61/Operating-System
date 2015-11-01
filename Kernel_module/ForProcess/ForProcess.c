#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");


int functn_init(void){
	struct task_struct *task;
	for_each_process(task){
		printk("%s [%d]\n",task->comm,task->pid);
	}
	return 0;
}

void functn_cleanup(void){
	printk(KERN_INFO "Cleaning Up.\n");
}

module_init(functn_init);
module_exit(functn_cleanup);
