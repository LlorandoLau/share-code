#include <linux/module.h>
#include <linux/init.h>
MODULE_LICENSE("GPL");
static int __init __module_address_init(void);
static void __exit __module_address_exit(void);

int a_module()
{
	return 0;
}

int __module_address_init(void)
{
	struct module *ret;
	unsigned long addr=(unsigned long)a_module;

	preempt_disable();
	ret=__module_address(addr);
	preempt_enable();

	if(ret!=NULL)
	{
		printk("<0>ret->name: %s\n",ret->name);
		printf("<0>ret->state: %s\n",ret->state);
		printk("<0>ret->core_size: %d\n",ret->core_size);

	}else{
		rintk("<0>__module_address return null\n");
	}
	return 0;

}

void __module_address_exit(void)
{
	printf("<0>module exit ok\n");
}

module_init(__module_address_init);
module_exit(__module_address_exit);
