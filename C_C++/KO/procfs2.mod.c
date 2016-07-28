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
	{ 0x74dfe657, __VMLINUX_SYMBOL_STR(seq_release) },
	{ 0x9820322b, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x5d0734b8, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x9c7796d4, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0xf853d021, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x6172b936, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x7d228c7a, __VMLINUX_SYMBOL_STR(seq_open) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "19D0B59FE8DED98E6F11DEA");
