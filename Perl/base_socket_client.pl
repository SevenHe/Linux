#!/usr/bin/perl -w
use Socket;

# 创建一个套接字
socket(Server, PF_INET, SOCK_STREAM, getprotobyname('tcp'));

# 制作远端机器的地址
$internet_addr = inet_aton($remote_host)
	or die "Couldn't convert $remote_host into  an Internet address: $!\n";
$paddr = sockaddr_in($remote_port, $internet_addr);

# 联接
connect(Server, $paddr)
	or die "Couldn't connect to $remote_host:$remote_port: $!\n";

select((select(Server), $| = 1)[0]);   # 打开命令缓冲

# 通过套接字发送一些东西
print Server "Why don't you call me anymore?\n";

# 读取远端的响应
$answer = <Server>;

# 处理完之后终止联接
close(Server);
 
