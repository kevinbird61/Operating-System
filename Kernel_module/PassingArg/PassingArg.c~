/* Demonstrate command line argument passing to a module */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

/* License and Author */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kevin Chiu");

/* For variable defined */
static short int myshort = 1;
static int myint = 420;
static long mylong = 9999;
static char *myString = "blah";
static int myintArray[2] = {-1,-1};
static int arr_argc = 0;

/* module_param(foo,int,0000); 
The first parameter => parameter's name
The second parameter => data type 
The final parameter => permission bits,
for exposing parameters in sysfs (if non-zero) at a later stage
*/

module_param(myshort,short,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort,"A short integer");
module_param(myint,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint,"An integer");
module_param(mylong,long,S_IRUSR);
MODULE_PARM_DESC(mylong,"A long integer");
module_param(myString,charp,0000); // NOTICE : using 'charp' and permission bits is '0000'

/* module_param_array(name,type,num,perm);
name : parameter's name
type : data type
num : a pointer to the variable that will store the number of elements of the array initialized by the user at module loading time
perm : permission bits
*/
module_param_array(myintArray,int,&arr_argc,0000);
MODULE_PARM_DESC(myintArray,"An array of integers");

static int __exit PassingArg_init(void)
{
	int i;
	printk(KERN_INFO "Hello , world - PassingArg \n===============\n");
	printk(KERN_INFO "myshort is a short integer: %hd\n",myshort);
	printk(KERN_INFO "myint is a integer: %d\n",myint);
	printk(KERN_INFO "mylong is a long integer: %ld\n",mylong);
	printk(KERN_INFO "myString is a String : %s\n",myString);
	for(i=0;i<(sizeof myintArray / sizeof(int));i++){
		printk(KERN_INFO "myintArray[%d] = %d\n",i,myintArray[i]);
	}
	printk(KERN_INFO "got %d arguments for myintArray.\n",arr_argc);
	return 0;
}

static void __exit PassingArg_exit(void){
	printk(KERN_INFO "Goodbye , world in PassingArg\n");
}

module_init(PassingArg_init);
module_exit(PassingArg_exit);
