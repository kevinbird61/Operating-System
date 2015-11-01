#include <linux/module.h>
#include <linux/module.h>	/* Needed by all modules */
#include <linux/init.h>		/* Needed for the macros */

int init_func(void){
	printk("Hello World!\n");
	return 0;
}

void cleanup_func(void){
	printk("Goodbye world!\n");
}

module_init(init_func);
module_exit(cleanup_func);
