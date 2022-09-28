#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>

#define BUFFER_SIZE 128

#define PROC_NAME "jiff_seconds"

static long start=0;

ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos){
	.owner=THIS_MODULE;
	.read=proc_read;
};

//function is called when module loaded
int proc_init(void){
	//creates /proc entry
	proc_create(PROC_NAME,0,NULL, &proc_ops);
	printk(KERN_INFO "/proc/%s created\n",PROC_NAME);
	start=(long)jiffies;

	return 0;

}
//function is called when module removed
void proc_exit(void){
	//removed /proc entry
	remove_proc_entry(PROC_NAME,NULL);
	
	printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);

}
//function called each time /proc entry is read
ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos){
	int r=0;
	char buff[BUFFER_SIZE];
	static int done=0;

	if(done){
		done=0;
		return 0;
	}
	done=1;
	r=sprintf(buff, "Seconds: %lu\n", (jiffies-start)/HZ);

	//copies buff to usr_buf
	copy_to_user(usr_buf,buff,r);
}
module_init(proc_init);
module_exit(proc_exit);
