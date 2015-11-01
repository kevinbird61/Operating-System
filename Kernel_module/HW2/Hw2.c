/* Using seq_file to implement the for_each_process */
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/proc_fs.h> // proc_fs
#include <linux/seq_file.h> // seq_file
#include <linux/fs.h> // struct file , struct inode
#include <linux/sched.h> // next_task()

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kevin Chiu");
/* For passing Command Line argument */
char *command = "parentchild"; // set the default
pid_t pid = 0; // user designation about processor id

module_param(command,charp,0000);
MODULE_PARM_DESC(command,"User Command");
module_param(pid,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(pid,"User specify Pid");

/* ==========================For Reading all the Process========================== */
static int seqPro_proc_show(struct seq_file *m, void *v) {
  struct task_struct *task_list;
  for_each_process(task_list){
  	seq_printf(m, "%s [%d]\n",task_list->comm,task_list->pid);
  }
  return 0;
}

static int seqPro_proc_open(struct inode *inode, struct  file *file) {
  return single_open(file, seqPro_proc_show, NULL);
}

static const struct file_operations seqPro_proc_fops = {
  .owner = THIS_MODULE,
  .open = seqPro_proc_open, // For open
  .read = seq_read,
  .llseek = seq_lseek,
  .release = single_release,
};
/* ==========================For Reading all the Process========================== */

/* ==========================For Reading specify the Process========================== */
static int specify_proc_show(struct seq_file *m, void *v) {
  struct task_struct *current_task;
  int count=0;
  for_each_process(current_task){
  	if(current_task->pid == pid){
  		seq_printf(m,"The parent's name is [%s]\n",current_task->parent->comm);
  		count++;
  		//seq_printf(m, "The child's name is [%s]\n",child_task->comm);
  	}
  	if(current_task->parent->pid == pid){
  		seq_printf(m,"The child's name is [%s]\n",current_task->comm);
  		count++;
  	}
  	if(count==2){
  		break;
  	}
  }
  return 0;
}

static int specify_proc_open(struct inode *inode, struct  file *file) {
  return single_open(file, specify_proc_show, NULL);
}

static const struct file_operations specify_proc_fops = {
  .owner = THIS_MODULE,
  .open = specify_proc_open, // For open
  .read = seq_read,
  .llseek = seq_lseek,
  .release = single_release,
};
/* ==========================For Reading specify the Process========================== */
static int __init hw2_proc_init(void) {
	if(!strcmp(command,"showall")){
		proc_create("hw2_proc", 0, NULL, &seqPro_proc_fops);
	}
	else if(!strcmp(command,"parentchild")){
		proc_create("hw2_proc", 0, NULL, &specify_proc_fops);
	}
	else{
		/* Output : /var/log/kern.log */
		printk(KERN_INFO "Error Command!\n");
	}
	return 0;
}

static void __exit hw2_proc_exit(void) {
	remove_proc_entry("hw2_proc", NULL);
}

module_init(hw2_proc_init);
module_exit(hw2_proc_exit);
