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
	{ 0xdaef32a8, __VMLINUX_SYMBOL_STR(param_ops_short) },
	{ 0xa5f62949, __VMLINUX_SYMBOL_STR(param_ops_long) },
	{ 0x5d8a8204, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0x9d7fe6cc, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2079f155, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "FA9E942F04C4826AA5B5862");
