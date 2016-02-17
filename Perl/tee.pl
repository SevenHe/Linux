#!/usr/bin/perl
use	warnings; 

tee("/tmp/foo", "/tmp/bar", "/tmp/glarch");

while(<>) {
	last if /end/;
	print "$ARGV at line $. => $_";
}

close(STDOUT)   or die "can't close STDOUT:$!";

sub tee {
	my @output = @_;
	my @handles = ();
	for my $path (@output) {
		my $fh;      # open 会填充这些
		unless (open ($fh, ">", $path)) {
			warn "cannot write to $path: $!";
			next;
		}
		push @handles, $fh;
	}

	# parent process will die here!
	return if my $pid = open(STDOUT, "|-");
    die "cannot fork: $!" unless defined $pid;	

	# process the STDIN in the child process!
	while(<STDIN>) {
		for my $fh (@handles) {
			print $fh $_ and print "take your input $_ into $fh\n" or die "tee output failed:$!";
			last if /end/;
		}
	}

	for my $fh (@handles) {
		close($fh) or die "tee closing failed: $!";
	}
	exit;      # 不让子进程返回到主循环！
}
#badfunc("arg");            # TMD，跑！
#$string = forksub(\&badfunc, "arg");   # 把它当作字串捕获
#@lines = forksub(\&badfunc, "arg");   # 当作独立的行
#
#sub forksub {
#	my $kidpid = open my $self, "-|";
#	defined $kidpid   or die "cannot fork: $!";
#	shift->(@_), exit   unless $kidpid;
#	local $/      unless wantarray;
#	return <$self>;         # 当退出范围的时候关闭
#}

