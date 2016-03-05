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

# oct
$perms = (stat("filename"))[2] & 07777; $oct_perms = sprintf "%lo", $perms; 

# open
{
	my $fh;         #（未初始化）
	open($fh, ">logfile")   # $fh 被自动激活
		or die "Can't create logfile: $!";
	...         # 干点别的
}            # $fh 在这里关闭

#模式	读访问	写访问	只附加	不存在时创建	删除现有的
#< PATH		Y		N		N		N				N
#> PATH		N		Y		N		Y				Y
#>> PATH	N		Y		Y		Y				N
#+< PATH	Y		Y		N		N				N
#+> PATH	Y		Y		N		Y				Y
#+>> PATH	Y		Y		Y		Y				N
#｜ COMMAND	N		Y		n/a		n/a				n/a
#COMMAND ｜	Y		N		n/a		n/a				n/a
# 在这些符号‘<,>’等后面使用&，则复制一个文件句柄！
# 表29-2 I/O 纪律
# 纪律	含义
# :raw	二进制模式；不做处理
# :text	缺省文本处理
# :def	use open 的缺省声明
# :latin1	文件应该是 ISO-8859-1
# :ctype	文件应该是 LC_CTYPE
# :utf8	文件应该是 UTF-8
# :utf16	文件应该是 UTF-16
# :utf32	文件应该是 UTF-32
# :uni	直观 Unicode（UTF-*）
# :any	直观 Unicode/Latin1/LC_CTYPE
# :xml	使用文件中声明的编码
# :crlf	直观换行符
# :para	段落模式
# :slurp	吞噬模式
open(FH, "<:para:crlf:uni", $path) or die "can't open $path: $!";
while ($para = )   { ... }

open(INPUT, "-") or die;      # 重新打开标准输入用于读取
open(INPUT, "<-") or die;      # 同样的事情，不过是明确声明
open(OUTPUT, ">-") or die;       # 重新打开标准输出用于写

# opendir DIRHANDLE, EXPR; ord EXPR/ord; 
# pack TEMPLATE, LIST
# 表29-3，pack/unpack 的摸板字符
# 字符	含义
# a	一个填充空的字节串
# A	一个填充空格的字节串
# b	一个位串，在每个字节里位的顺序都是升序
# B	一个位串，在每个字节里位的顺序都是降序
# c	一个有符号 char（8位整数）值
# C	一个无符号 char（8位整数）值；关于 Unicode 参阅 U
# d	本机格式的双精度浮点数
# f	本机格式的单精度浮点数
# h	一个十六进制串，低四位在前
# H	一个十六进制串，高四位在前
# i	一个有符号整数值，本机格式
# I	一个无符号整数值，本机格式
# l	一个有符号长整形，总是 32 位
# L	一个无符号长整形，总是 32 位
# n	一个 16位短整形，“网络”字节序（大头在前）
# N	一个 32 位短整形，“网络”字节序（大头在前）
# p	一个指向空结尾的字串的指针
# P	一个指向定长字串的指针
# q	一个有符号四倍（64位整数）值
# Q	一个无符号四倍（64位整数）值
# s	一个有符号短整数值，总是 16 位
# S	一个无符号短整数值，总是 16 位
# u	一个无编码的字串
# U	一个 Unicode 字符数字
# v	一个“VAX”字节序（小头在前）的 16 位短整数
# V	一个“VAX”字节序（小头在前）的 32 位短整数
# w	一个 BER 压缩的整数
# x	一个空字节（向前忽略一个字节）
# X	备份一个字节
# Z	一个空结束的（和空填充的）字节串
# @	用空字节填充绝对位置

# pipe READHANDLE, WRITEHANDLE
pipe(README, WRITEME);
unless ($pid = fork) {   #    子进程
	defined $pid or die "can't fork: $!";
	close(README);
	for $i (1..5) { print WRITEME "line $i\n" }
	exit;
}
$SIG{CHLD} = sub { waitpid($pid, 0) };
close(WRITEME);
@strings = ;
close(README);
print "Got:\n", @strings;

# pop ARRAY
# pop

# pos SCALAR
# pos
# 这个函数返回上一次 m//g 对 SCALAR 搜索在 SCALAR 中留下来的位置。它返回在最后一个匹配 字符后面的字符的偏移量。

# print FILEHANDLE LIST
# print LIST
# print
print { $OK ? "STDOUT" : "STDERR" } "stuff\n";
print { $iohandle[$i] } "stuff\n";

# prototype FUNCTION
# 把一个函数的原形当作字串返回（如果该函数没有原型返回，undef）。FUNCTION 是一个指向你 想知道原型的函数的引用或者名字。

# push ARRAY, LIST
splice @array, @array, 0, listfunc();
# the most efficient!
for(;;) {
	push @array, shift @array;
}

# q/STRING/
# qq/STRING/
# qr/STRING/
# qw/STRING/
# qx/STRING/

# quotemeta EXPR, 实现逃逸

# rand
$roll = int(rand 6) + 1;      # $roll 现在是一个介于 1 和 6 之间的数字

# read FILEHANDLE, SCALAR, LENGTH, OFFSET
# read FILEHANDLE, SCALAR, LENGTH
while(read(FROM, $buf, 16384)) {
	print TO $buf;
}

# readdir
@allfiles = grep { $_ ne '.' and $_ ne '..' } readdir THISDIR;
@allfiles = grep !/^\./, readdir THISDIR;
@textfiles = grep -T, readdir THISDIR;
# readdir 不在当前目录
opendir(THATDIR, $path) or die "can't opendir $path: $!";
@dotfile = grep { /^\./ && -f } map { "$path/$_" } readdir(THATDIR);
closedir THATDIR;

# readline!
$line = ;
$line = readline(STDIN);      # 和上面一样
$line = readline(*STDIN);      # 和上面一样
$line = readline(\*STDIN);      # 和上面一样

# readlink, to judge the path-to-file is a link or not.

# recv SOCKET, SCALAR, LEN, FLAGS, use in socket!

# redo 操作符在不经重新计算条件的情况下重新开始一个循环块。如果存在任何 continue 块也 不会执行它们。如果省略了 LABEL，那么该操作符指向最内层的闭合循环。

# ref, 如果这个引用的对象已经赐福到了一个包中，那么返回的就是该包的名字。你可以把 ref 当作一种 “类型是”操作符。
if (ref($r) eq "HASH") {
	print "r is a reference to a hash.\n";
}
elsif (ref($r) eq "Hump") {      # 烦人——见下文
	print "r is a reference to a Hump object.\n"
}
elsif (not ref $r) {
	print "r is not a reference at all.\n";
}
if ($r->isa("Hump") ){
	print "r is a reference to a Hump object, or subclass.\n"
}

# rename, require!

# reverse LIST/HASH in list environment!
for (reverse 1 .. 10) { ... }
%barfoo = reverse %foobar;

# rewinddir!

# rindex STR, SUBSTR, POSITION
# rindex STR, SUBSTR
$pos = length $string;
while (($pos = rindex $string, $lookfor, $pos) >= 0) {
	print "Found at $pos\n";
	$pos--;
}

# rmdir ..., File::Path!!

# scalar, to make it compulsively in a scalar environment!

# seek FILEHANDLE, OFFSET, WHENCE, whence:0，文件 开头；1 文件的当前位置；2，文件结尾
# refer to IO::Seekable
for (;;) {
	for ($curpos = tell FILE;   ;   $curpos = tell FILE) {
		grok($_);         # 处理当前行
	}
	sleep $for_a_while;
	seek FILE, $curpos, 0;      # 重置 end-of-file 错误。
}

# seekdir DIRHANDLE, POS

# select FILEHANDLE
# select, $|: means autoflush if not 0!
my $oldfh = select STDER; $| = 1; select $oldfh;

# select RBITS, WBITS, EBITS, TIMEOUT
($nfound, $timeleft) = 
	select($rout=$rin, $wout=$win, $eout=$ein, $timeout);
select undef, undef, undef, 4.75;

# semctl ID, SEMNUM, CMD, ARG; semget KEY, NSEMS, SIZE, FLAGS; semop KEY, OPSTRING
# IPC::SysV, IPC:Semaphore
$semop = pack "s*", $semnum, -1, 0;
semop $semid, $semop or die "Semaphore trouble: $!\n";

# send SOCKET, MSG, FLAGS, TO
# send SOCKET, MSG, FLAGS

# setpgrp PID, PGRP
# setpriority WHICH, WHO, PRIORITY

# setsockopt SOCKET, LEVEL, OPTNAME, OPTVAL
use Socket;
socket(SOCK, ...) or die "Can't make socket: $!\n";
setsocket(SOCK, SOL_SOCKET, SO_REUSEADDR, 1)
	or warn "Can't do setdosockotp: $!\n";

# shift
while (defined($_ = shift)) {
	/^[^-]/     && do { unshift @ARGV, $_; last };
	/^-w/       && do { $WARN = 1;         next };
	/^-r/       && do { $RECURSE = 1;      next };
	die "Unknown argument $_\n";
}

# shmctl ID, CMD, ARG
# shmget KEY, SIZE, FLAGS
# shmread ID, VAR, POS, SIZE
# shmwrite ID, STRING, POS, SIZE

# shutdown SOCKET, HOW
shutdown(SOCK, 0);   # 不许再读
shutdown(SOCK, 1);   # 不许再写
shutdown(SOCK, 2);   # 不许再 I/O

print SERVER "my request\n";   # 发送一些数据
shutdown(SERVER, 1);         # 发送完毕，没有更多要发的东西了
$answer = < SERVER >;         # 但你还可以读

# sin, sleep

# socket SOCKET, DOMAIN, TYPE, PROTOCOL; use Socket!

# socketpair SOCKET1, SOCKET2, DOMAIN, TYPE, PROTOCOL
use Socket;
socketpair(Rdr, Wtr, AF_UNIX, SOCK_STREAM, PF_UNSPEC);
shutdown(Rdr, 1);      # 不允许读者写
shutdown(Wtr, 0);      # 不允许写者读 

# sort USERSUB LIST
# sort BLOCK LIST
# sort LIST
sub numerically { $a <=> $b }
@sortedbynumber = sort numerically 53,29,11,32,7;
@descending = reverse sort numerically 53,29,11,32,7;

sub reverse_numerically { $b <=> $a }
@descending = sort reverse_numerically 53,29,11,32,7;

@unsorted = qw/sparrow Ostrich LARK catbird blueJAY/;
@sorted = sort { lc($a) cmp lc($b) } @unsorted;

sub bysales { $sales_amount{$b} <=> $sales_amount{$a} }

for $dept (sort bysales keys %sale_amount) {
	print "$dept => $sales_amount{$dept}\n";
}

sub by_sales_then_dept {
	$sales_amount{$b} <=> $sales_amount{$a}
	||
	$a cmp $b
}
# map-sort-map
for $dept (sort by_sales_then_dept keys %sale_amount) {
	print "$dept => $sales_smount{$dept}\n";
}

@sorted_lines = map { $_->[0] }
	sort {
		@a_fields = @$a[1..$#$a];
		@b_fields = @$b[1..$#$b];

		$a_fields[3] <=> $b_fields[3]
			||
		$a_fields[0] <=> $b_fields[0]
			||
		$b_fields[2] <=> $b_fields[2]
		}
	map { [$_, split /:/]} @lines;

# splice ARRAY, OFFSET, LENGTH, LIST
# splice ARRAY, OFFSET, LENGTH
# splice ARRAY, OFFSET
# splice ARRAY
# 	直接方法					splice 等效
# push(@a, $x, $y)			splice(@a, @a, 0, $x, $y)
# pop(@a)					splice(@a, -1)
# shift(@a)					splice(@a, 0, 1)
# unshift(@a, $x, $y)		splice(@a, 0, 0, $x, $y)
# $a[$x] = $y				splice(@a, $x, 1, $y)
# (@a, @a = ())				splice(@a)

# split /PATTERN/, EXPR, LIMIT
# split /PATTERN/, EXPR
# split /PATTERN/
# split
($login, $passwd, $remainder) = split /:/, $_, 3;

# sprintf FORMAT, LIST
# %%	一个百分号
# %c	一个带有给定数字的字符
# %s	一个字串
# %d	一个有符号整数，十进制
# %u	一个无符号整数，十进制
# %o	一个无符号整数，八进制
# %x	一个无符号整数，十六进制
# %e	一个浮点数，科学记数法表示
# %f	一个浮点数，用固定的小数点表示
# %g	一个浮点数，以 %e 或 %f 表示
# %X	类似 %x，但使用大写字符
# %E	类似 %e，但使用大写的“E”
# %G	类似 %g，但是带一个大写的“E”（如果正确的话）
# %b	一个无符号整数，二进制
# %p	一个指针（输出十六进制的 Perl 值的地址）
# %n	特殊：把到目前为止输出的字符数放到参数列表中的下一个变量里
# %与转换字符之间：
# space		用空格前缀正数
# +			用加号前缀正数
# -			在域内左对齐
# -			用零而不是空格进行右对齐
# #			给非零八进制前缀“0”，给非零十六进制前缀“0x”
# number	最小域宽度
# .number	“精度”：浮点数的小数点后面的位数字串最大长度。整数最小长度
# l 		把整数解释成 C 类型的 long 或者 unsigned long
# h			把整数解释成 C 类型的 short 或者 unsigned short（如果没有提供标志，那么把整数解释成 C 类型 int 或者 unsigned）

# sqrt EXPR
# sqrt

# stat FILEHANDLE
# stat EXPR
# stat
($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size,
	      $atime, $mtime, $ctime, $blksize, $blocks)
	           = stat $filename;
# 索引	域		含义
# 0		$dev	文件系统的设备号
# 1		$ino	i 节点号码
# 2		$mode	文件模式（类型和权限）
# 3		$nlink	指向该文件的（硬）链接数量
# 4		$uid	文件所有者的数字用户 ID
# 5		$gid	文件所属组的数字组 ID
# 6		$rdev	设备标识符（只用于特殊文件）
# 7		$size	文件的总尺寸，以字节计
# 8		$atime	自纪元以来以秒计的上一次访问时间
# 9		$mtime	自纪元以来以秒计的上一次修改时间
# 10	$ctime	自纪元以来以秒计的上一次i节点改变的时间（不是创建时间！）
# 11	$blksize	选定的用于文件系统 I/O 的块尺寸
# 12	$blocks		实际分配的块数量

# study SCALAR
# study
@pats = ();
foreach $word (@words) {
	push @pats, qr/\b${word}\b/i;
}
@ARGV = @files;
undef $/;      # 吃进每个完整的文件
while (<>) {
	for $pat (@pats) {
		$seen{$ARGV}++ if /$pat/;
	}
}
$/ = "\n";      # 恢复正常的输入终止符
foreach $file (sort keys(%seen)) {
	print "$file\n";
}

# sub NAME PROTO ATTRS BLOCK
sub numstrcmp ($$) : locked {
	my ($a, %b) = @_;
	return $a <=> $b || $a cmp %b;
}

# substr EXPR, OFFSET, LENGTH, REPLACEMENT
# substr EXPR, OFFSET, LENGTH
# substr EXPR, OFFSET
# $var is the string to be changed!
substr($var, 0, 0) = "Larry";
substr($var, 0, 1) = "Moe";
substr($var, -1) = "Curly";
$oldstr = substr($var, -1, 1, "Curly");
substr($var, -10) =~ s/ /./g;

# symlink OLDNAME, NEWNAME
# syscall LIST, refer to POSIX::

# sysopen FILEHANDLE, FILENAME, MODE, MASK
# sysopen FILEHANDLE, FILENAME, MODE 
# 标志	    		含义
# O_RDONLY		只读
# O_WRONLY		只写
# O_RDWR		读和写
# O_CREAT		如果文件不存在则创建之
# O_EXCL		如果文件已经存在则失败
# O_APPEND		附加到文件上
# O_TRUNC		截断该文件
# O_NONBLOCK	非阻塞访问
# refer to IO::File or IO::Handle

# sysseek FILEHANDLE, POSITION, WHENCE
# system PATHNAME LIST
# system LIST
@args = ("command", "arg1", "arg2");
system(@args) == 0
	or die "system @args failed: $?"

# syswrite FILEHANDLE, SCALAR, LENGTH, OFFSET
# syswrite FILEHANDLE, SCALAR, LENGTH
# syswrite FILEHANDLE, SCALAR
# do not mingle them(read or write or others except sysread)!
use Errno qw/EINTR/;
$blksize = (stat FROM)[11] || 16384;      # 选定的块大小？
while ($len = sysread FROM, $buf, $blksize) {
	if (!defined $len) {
		next if $! == EINTR;
		die "System read error: $!\n"
	}
	$offset = 0;
	while ($len) {            # 处理部分写问题
		$written = syswrite TO, $buf, $len, $offset;
		die "System write error: $!\n" unless defined $written;
		$offset   += $written;
		$len   -= $written;
	}
}

# tell FILEHANDLE
# tell, 返回文件句柄当前的pos

# tie VARIABLE, CLASSNAME, LIST
# 此函数把一个变量和一个类绑定在一起，而该类提供了该变量的实现。VARIABLE 是要绑定的变量 （标量，数组，或者散列）或者类型团（代表一个文件句柄）。CLASSNAME 是实现一个正确类型的 类名字。
# 一个实现散列的类应该提供下列方法：
# TIEHASH CLASS, LIST
# FETCH SELF, KEY
# STORE SELF, KEY, VALUE
# DELETE SELF, KEY
# CLEAR SELF
# EXISTS SELF, KEY
# FIRSTKEY SELF
# NEXTKEY SELF, LASTKEY
# DESTROY SELF
# 一个实现普通数组的类应该提供下列方法：
# TIEARRAY CLASS, LIST
# FETCH SELF, SUBSCRIPT
# STORE SELF, SUBSCRIPT, VALUE
# FETCHSIZE SELF
# STORESIZE SELF, COUNT
# CLEAR SELF
# PUSH SELF, LIST
# POP SELF
# SHIFT SELF
# UNSHIFT SELF, LIST
# SPLICE SELF, OFFSET, LENGTH, LIST
# EXTEND SELF, COUNT
# DESTROY SELF
# 一个实现标量的类应该提供下列方法：
# TIESCALAR CLASS, LIST
# FETCH SELF,
# STORE SELF, VALUE
# DESTROY SELF
# 一个实现文件句柄的类应该提供下列方法：
# TIEHANDLE CLASS, LIST
# READ SELF, SCALAR, LENGTH, OFFSET
# READLINE SELF
# GETC SELF
# WRITE SELF, SCALAR, LENGTH, OFFSET
# PRINT SELF, LIST
# PRINTF SELF, FORMAT, LIST
# CLOSE SELF
# DESTROY SELF
# refer to Tie::Hash/Array/Scalar/Handle!

# tied VARIABLE
ref tied %hash;
# 找出你的散列与哪个包捆绑。(假设你忘记了。)

# time
$start = time();
system("some slow command");
$end = time();
if ($end - $start > 1) {
	print "Program started: ", scalar localtime($start), "\n";
	print "Program ended:  ", scalar localtime($end), "\n";
}  

# times
($user, $system, $cuser, $csystem) = times();
printf "This pid and its kids have consumed %.3f seconds\n",
	$user + $system + $cuser + $csystem;
# return user's consumable time in the scalar enviroment!
$stat = times();
...
$end = times();
printf "that took %.2f CPU seconds of user time\n",
	$end - $start;

# truncate FILEHANDLE, LENGTH
# truncate EXPR, LENGTH
# just for file!
# uc EXPR
# uc
# ucfirst EXPR
# ucfirst
# umask EXPR
# umask
# undef EXPR
# undef
# unlink LIST
# unlink

# unpack TEMPLATE, EXPR
$_ = <> until ($mode, $file) = /^begin\s*(\d*)\s*(\S*)/;
open(OUT, "> $file") if $file ne "";
while (<>) {
	last if /^end/;
	next if /[a-z]/;
	next unless int((((ord() - 32) & 077) + 2) / 3) == int (length() / 4);
	print OUT unpack "u", $_;
}
chmod oct($mode), $file;

# unshift ARRAY, LIST
# untie VARIABLE
# use MODULE VERSION LIST
# use MODULE VERSION ()
# use MODULE VERSION
# use MODULE LIST
# use MODULE ()
# use MODULE
# use VERSION

# utime LIST
$day = 24 * 60 * 60;         # 24 小时的秒数
$later = time() + 30 * $day;   # 30 天接近一个月
utime $later, $later, @ARGV;	# just like 'touch'

# values HASH
# vec EXPR, OFFSET, BITS
# vec 函数制造一个存储紧凑的无符号整数的列表。
$bitstring = "";
$offset = 0;

foreach $num (0, 5, 5, 6, 2, 7, 12, 6) {
	vec($bitstring, $offset++, 4) = $num;
}

# wait
# waitpid PID, FLAGS
# harvest zombie processes!
use POSIX ":sys_wait_h";
do {
	$kid = waitpid(-1, &WNOHANG);
} until $kid == -1;

# wantarray
return unless defined wantarray;      # 不需要干什么事情
my @a = complex_calculation();
return wantaray ? @a : \@a;

# warn LIST
# warn
# write FILEHANDLE
# write

