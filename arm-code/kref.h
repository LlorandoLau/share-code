#include <linux/kernel.h>
#include <linux/module.h>
 /*
 KERN_INFO:打印等级，77777
 printk(KERN_INFO"kreftest_init\n");
 */
struct my_obj
 {
        int val;
        struct kref refcnt;
};
 
struct my_obj *obj;
 
void obj_release(struct kref *ref)
{
        struct my_obj *obj = container_of(ref, struct my_obj,refcnt);
        printk(KERN_INFO"obj_release\n");
        kfree(obj);     //释放空间
}
 
static int __init kreftest_init(void)
{
        printk(KERN_INFO"kreftest_init\n");
        obj= kmalloc(sizeof(*obj),GFP_KERNEL);
        kref_init(&obj->refcnt);
        return 0;
}
 
static void __exit kreftest_exit(void)
{
        printk(KERN_INFO"kreftest_exit\n");
        kref_put(&obj->refcnt,obj_release);
        return;
}
 
module_init(kreftest_init);
module_exit(kreftest_exit);
 
MODULE_LICENSE("GPL");