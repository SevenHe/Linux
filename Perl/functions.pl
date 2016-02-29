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
