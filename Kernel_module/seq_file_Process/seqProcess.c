/* Using seq_file to implement the for_each_process */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h> // proc_fs
#include <linux/seq_file.h> // seq_file
#include <linux/fs.h> // struct file , struct inode
#include <linux/sched.h> // next_task()

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

static int __init seqPro_proc_init(void) {
  proc_create("seqPro_proc", 0, NULL, &seqPro_proc_fops);
  return 0;
}

static void __exit seqPro_proc_exit(void) {
  remove_proc_entry("seqPro_proc", NULL);
}

MODULE_LICENSE("GPL");
module_init(seqPro_proc_init);
module_exit(seqPro_proc_exit);

