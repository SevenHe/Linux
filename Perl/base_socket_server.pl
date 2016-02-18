use Socket;

# 创建套接字
socket(Server, PF_INET, SOCK_STREAM, getprotobyname('tcp'));

# 为了我们可以快速重起服务器
setsockopt(Server, SOL_SOCKET, SO_REUSEADDR, 1);

# 制作自己的套接字地址
$my_addr = sockaddr_in($server_port, INADDR_ANY);
bind(Server, $my_addr)
	or die "Couldn't bind to port $server_port: $!\n";

# 为来访联接建立一个队列
listen(Server, SOMAXCONN)
	or die "Couldn't listen on port $server_port: $!\n";

# 接受并处理任何联接
while(accept(Client, Server)) {
        # 在新建的客户端联接上做些处理
}

close(Server);

REQUEST:
while (accept(Client, Server)) {
	if ($kidpid = fork) {
		close Client;      # 父进程关闭不用的句柄
		next REQUEST;
	}
	defined($kidpid)   or die "cannot fork: $!";


	close Server;         # 子进程关闭无用的句柄

	select(Client);      # 打印用的新的缺省句柄
	$| = 1;         # 自动刷新

	# child process communicates with the client!
	$input= <Client>;
	print Client "output\n";   # 或者 STDOUT，一样的东西

	open(STDIN, "<<&Client")   or die "can't dup client: $!";
	open(STDOUT, ">&Client")   or die "can't dup client: $!";
	open(STDERR, ">&Client")   or die "can't dup client: $!";

	# execute the bc, just a example.
	system("bc -l");      # 或者任何你喜欢的东西，只要它不会逃逸出 shell
	print "done\n";      # 仍然是给客户端
	close Client;
	exit;         # 不让子进程回到 accept!
}
