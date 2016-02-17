open(INPUT, "< /etc/motd")   or die "/etc/motd: $!";
if ($pid = fork) { waitpid($pid, 0);}
else {
	defined($pid)   or die "fork: $!";
	while (<INPUT>) { print "$.: $_" }
	exit;   # 不让子进程回到主代码
}
# INPUT 句柄现在在父进程里位于 EOF
