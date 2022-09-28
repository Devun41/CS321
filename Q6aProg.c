#include<linux/init.h>
#include<linux/module.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/kernel,h>
#include <linux/jiffies.h>

#define BUFFER_SIZE 128

#define PROC_NAME "jiffies"

ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos);

static struct file_operations proc_ops = {
	.owner = THIS_MODULE,
	.read = proc_read,
};

//function called when modules loaded
int proc_init(void){
//creates /proc entry
	proc_create(PROC_NAME, 0, NULL, &proc_ops);
	printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
	
	return 0;

}
//function called when module removed
void proc_exit(void){
//removes /proc entry
	remove_proc_entry(proc-name, NULL);
	printk(KERN_INFO "/proc/%s removed\n",PROC_NAME);

}
//function called when /proc entry is loaded
ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos){
	int r=0;
	char buff(BUFFER_SIZE);
	static int done=0;

	if(done){
		done=0;
		return 0;
	}
	done=1;
	rv=sprintf(buff, "Jiffies: %lu\n", jiffies);

	//copies buff to usr_buf
	copy_to_user(usr_buf,buff,r);
	
	return r;

}
module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dev");
MODULE_DESCRIPTION("Jiffies Module");