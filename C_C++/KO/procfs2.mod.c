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
	{ 0xbc884195, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x99c6d79, __VMLINUX_SYMBOL_STR(seq_release) },
	{ 0x839184c, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x97191659, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa1613fa9, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x13e72d7b, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x5d0785ce, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x51e8021b, __VMLINUX_SYMBOL_STR(seq_open) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "19D0B59FE8DED98E6F11DEA");
