#!/usr/bin/perl -w

@cannot = grep {not chmod 0755, $_} 'file1', 'file2', 'file3';
die "$0: could no chmod @cannot\n" if @cannot;

$last_char = chop($var);
#$last_char = substr($var, -1, 1, "" );   # 一样的东西
substr($caravan, -5) = " ";

sub chown_by_name {
	my($user, @files) = @_;
	chown((getpwnam($user))[2,3], @files) == @files
		or die "can't chown @files: $!";
}

# some ftp servers do this!
chroot((getpwname('ftp'))[7])
	or die "Can't do anonymous ftp: $!\n";

use  Socket;

my ($remote, $port) = ("www.perl.com", 80);
my $destaddr = sockaddr_in($port, inet_aton($remote));
connect SOCK, $destaddr
	or die "Can't connect to $remote at port $port: $!";

# crypt!
$pwd = (getpwuid ($<))[1];   # 假设我们在 Unix 上。

system "stty -echo";      # 或者看看 CPAN 上的 Term::ReadKey
print "Password: ";
chomp($word = );
print "\n";
system "stty echo";

if (crypt($word, $pwd) ne $pwd) {
	die "Sorry...\n";
} else {
	print "ok\n";
}

# dbmopen!
use DB_File;
dbmopen(%NS_Hist, "$ENV{HOME}/.netscape/history.dat", undef_
		or die "Can't open netscape history file: $!";

	while (($url, $when) = each %NS_Hist) {
		next unless defined($when);
		chop($url, $when);      # 删除尾部的空字节
		printf "Visited %s at %s.\n", $url,
		scalar(localtime(unpack("V",$when)));
	}

# defined! Diagnose whether the @ary runs out or not.
print "$val\n" while defined($val = pop(@ary));
# judge the subroutine!
indir("funcname", @arglist);
sub indir {
	my $subname = shift;
	no restrict 'refs';      #这样我们就可以使用间接地使用 subname
	if (defined &$subname) {
		&$subname(@_);   # 或者 $subname->(@_);
	}
	else {
		warn "Ignoring call to invalid function $subname";
	}
}

# 设置一个散列数组的数组
$dungeon[$x][$y] = \%properties;

# 从散列中删除一个属性
delete $dungeon[$x][$y]{"OCCUPIED"};

# 一次从散列中删除三个属性
delete @{ $dungeon[$x][$y] }{ "OCCUPIED", "DAMP", "LIGHTED" };

# 从数组中把 %properties 的引用删除
delete $dungeon[$x][$y];

# effective!
@array = ();      # 彻底清空 @array
undef @array;      # 忘记 @array 曾经存在过

# each!
while(($key, $value) = each %ENV) { 
	print "$key =$value\n"; 
} 

# eof!
while (<>) {
	next if /^\s*#/;   # 忽略注释
	print "$.\t$_";
} continue {
	close ARGV if eof;   # 不是 eof()！
}

# eval! just like 'try {} catch{} '
$op = shift;
for (@ARGV) {
	$was = $_;
	eval $op;
	die if $@;
	# 下一行调用内建函数，而不是同名的脚本       
	rename($was, $_) unless $was eq $_;
}

# exec, use PATHNAME to ensure the security!
exec { $args[0] } @args   # 就算是只有一个元素的列表也安全了
      or die "can't exec @args: $!";

# exit/ POSIX:_exit!
$ans = 
   exit if $ans =~ /^[Xx]/;

# fcntl !!
use Fcntl qw(F_GETFL F_SETFL O_NONBLOCK);

$flags = fcntl(REMOTE, F_GETFL, 0)
	or die "Can't get flags for the socket: $!\n";

$flags = fcntl(REMOTE, F_SETFL, $flags| O_NONBLOCK)
	or die "Can't set flags for teh socket: $!\n";

# fileno!
if (fileno(THIS) == fileno(THAT) ) {
	print "THIS and THAT are dups\n";
}

# flock!
use Fcntl qw/:flock/;      # 输出 LOCK_* 常量
sub mylock {
	flock(MBOX, LOCK_EX)
		or die "can't lock mailbox: $!";
	# 预防在我们等待的时候有家伙附加
	# 以及我们的 stdio 缓冲区失准
	seek(MBOX, 0, 2)
		or die "can't seek to the end of mailbox: $!";
}

open(mbox, ">>/USR/SPOOL/MAIL/$ENV{'USER'}")
	or die "can't open mailbox: $!";

mylock();
print MBOX $msg, "\n\n";
close MBOX	
	or die "can't close mailbox: $!";

# fork!!
use Errno qw(EAGAIN);
FORK: {
	if ($pid = fork) {
		# 父进程在此
		# 在 $pid 里可以看到子进程的进程 id
	}
	elsif (defined $pid) {   # 如果定义了，$pid 在这里是 0
		# 子进程在此
        # 你可以用 getppid 在这里获取父进程的 pid
	}
	elsif ($! == EAGAIN) {
        # EAGAIN 是认为可以恢复的 fork 错误
        sleep 5;
        redo FORK;
	}
	else {
		# 奇怪的 fork 错误                                  
		die "Can't fork: $!\n";
	}
}

# getc!can manipulate a specified file handle or stdin!
if ($BSD_STYLE) {
	system "stty cbreak /dev/tty 2>&1"
} else {
	system "stty", "-icanon", "eol", "......";
}

$key = getc;

if ($BSD_STYLE) {
	system "stty -cbreak /dev/tty 2>&1";
} else {
	system "stty", "icanon", "eol", "^@";    # ASCII NUL
}

print "\n";

# User:gerent!

# getgrgid, getgrnam

# gethostbyaddr
use Socket;
($name, $aliases, $addrtype, $length, @addrs) =
      gethostbyaddr($packed_binary_address, $addrtype); # list environment!
$ipaddr = inet_aton("127.0.0.1");      # localhost/just like v127.0.0.1
$claimed_hostname = gethostbyaddr($ipaddr, AF_INET);

# gethostbyname
($name, $aliases, $addrtype, $length, @addrs) = gethostbyname ($remote_hostname);

# Net::hostent!

# getlogin() || getpwuid($<)[0] 

# Net::netent! 

# getpgrp, getppid,    $curprio = getpriority(0, 0); 

# Net::proto

# User::pwent
# Net::Servent

# getsockname, getsockopt  
user Socket;
$mysockaddr = getsockname(SOCK);
($port, $myaddr) = sockaddr_in($mysockaddr);
$myname = gethostbyaddr($myaddr, AF_INET);
printf "I am %s [%vd]\n", $myname, $myaddr;

# glob, to use shell wildcard!
open(MAILRC, "~/.mailrc")      # 错：波浪号是一个 shell 的东西
	or die "can't open ~/.mailrc: $!";

open(MAILRC, (glob("~/.mailrc"))[0])   # 先扩展波浪号
	or die "can't open ~/.mailrc: $!";

# gmtime
use POSIX qw(strftime);
$now_string = strftime "%a %b %e %H:%M:%S %Y", gmtime;

# grep!EXPR: just like, 's///'
@out = grep {EXPR} @in;
@out = map { EXPR ? $_ : () } @in

# hex
$number = hex(ffff12c0);
sprintf "%lx", $number;

# index
$pos = -1;
while (($pos = index($string, $lookfor, $pos)) > -1) {
	print "Found at $pos\n";
	$pos++;
}

# int, because division in perl is for float numbers
$average_age = int 939/16;      # 结果是 58
$n = sprintf("%0.f", $f);      # 圆整到（不是截断）最接近的整数

# ioctl, Term::ReadKey is more portable!
require 'sys/ioctl.ph';

$size = pack("L", 0);
ioctl(FH, FIONREAD(), $size)
	or die "Couldn't call ioctl: $!\n";
$size = unpack("L", $size);

# join
$string = join "", @array;

# keys, desc!
foreach $key (sort {$hash{$b} <=> $hash{$a} } keys %hash) {
	printf "%4d %s\n", $hash{$key}, $key;
}

# kill
use Errno qw(ESRCH EPERM);
if (kill 0 => $minion) {
	print "$minion is alive!\n";
} elsif ( $! == EPERM) {         # UID 改变了
	print "$minion has escaped my control!\n";
} elsif ( $! == ESRCH) {
	print "$minion is deceased.\n";   # 或者是僵尸
} else {
	warn "Odd; I couldn't check on the status of $minion: $!\n";
}

# lc, lowercase; lcfirst
# length, 不要试图使用 length 寻找一个数组或者散列的大小。用 scalar @array 获取数组的尺寸， 用 scalar keys %hash 获取散列中键字/数值对的数量。（通常如果 scalar 多余则会把它 省略。）
$blen = do { use bytes;   length $string; }; # compute by bytes!

# link oldf, newf;
# listen
use Socket;
listen(PROTOSOCK, SOMAXCONN)
	or die "cannot set listen queue on PROTOSOCK: $!";

# localtime
($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime;

# lock! refer to Threads

# lstat, stat the link symbol if link symbol exists!

# map
%hash = map { genkey($_) => $_ } @array; 	# so similar to foreach!

# mkdir FILENAME, MASK; msgctl ID, CMD, ARG; msgrcv ID, VAR, SIZE, TYPE, FLAGS; msgsnd ID, MSG, FLAGS
# new CLASSNAME LIST!!
# no:参阅 use 操作符，它是 no 的反向操作符。大多数标准模块不会逆输入，把 no 当作一个 空操作，不过这正是它想要的。这个时候用法模块更具强制性。如果找不到 MODULE，那么抛出 一个例外。 
