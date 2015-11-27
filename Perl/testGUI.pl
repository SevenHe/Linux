#!/usr/bin/perl

use Gtk2;
use Encode qw/ encode decode /;  #加载encode模块，用来对中文编码

Gtk2 -> init;  #Gtk+程序初始化
my $win = Gtk2::Window -> new ( );  #建立一个新的窗口
$win -> set_title ( 'Hello world program' );  #设置窗口的标题
$win -> set_size_request ( 320,240 );  #设置窗口的大小为320 240
$win -> signal_connect ( destroy => sub { Gtk2 -> main_quit; } );  #设置程序退出信号
my $word = "Hello world\n".decode ( "euc-cn",'This is my first gui to use gtk!' );  
#在屏幕几的中央写的文字，中文需要utf8编码
my $label = Gtk2::Label -> new ($word);   #新建一个标签组件
$win -> add ($label);  #在窗口中添加这个标签组件
$win -> show_all;  #显示窗口中的所有元素
Gtk2 -> main;  #开始主循环
