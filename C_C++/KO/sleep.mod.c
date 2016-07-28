#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xeae23911, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x9c7796d4, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0xf853d021, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0xc3aaf0a9, __VMLINUX_SYMBOL_STR(__put_user_1) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0xd26137f0, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xe37ee3c1, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0xe420259e, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xf7d214d5, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x1b4288ff, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xc0a7fbee, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0x167e7f9d, __VMLINUX_SYMBOL_STR(__get_user_1) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "CFDEF1C1535B564BE5F4F96");
