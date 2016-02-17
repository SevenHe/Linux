our $zombies = 0;
$SIG{CHLD} = sub { $zombies++};
sub reaper {
	my $zombie;
	our %Kid_Status;   # 存储每个退出状态
	$zombies = 0;
	while (($zombie = waitpid( -1, WNOHANG)) != -1) {
		$Kid_Status{$zombie} = $?;
	}
}
while(1) {
	reaper() if $zombies;
	# ...
}
