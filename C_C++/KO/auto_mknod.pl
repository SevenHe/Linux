#!/usr/bin/perl
use warnings;

open(DEVS, "/proc/devices") 
	or die "Can not open the devices:$!";

$devno = 0;
$devname = "chardev";
$devminor = 111;	# random number!
while($line=<DEVS>)
{
	if($line =~ /$devname/)
	{
		$devno = (split / /, $line)[0];
		last;
	}
}
close(DEVS);
print "Get devno:", $devno, "\n";
# This is not the same like perl rules, it return a non-zero when failed!
$status = system("mknod $devname c $devno $devminor");
#$oks = system("echo ok");
#print "Make status: $status, \n";
print "Make completely!" if not $status; 
	
