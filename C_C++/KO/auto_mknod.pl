#!/usr/bin/perl
use warnings;

open(DEVS, "/proc/devices") 
	or die "Can not open the devices:$!";

$status = 0;
$devno = 0;
@devnames = ("chardev");
$devminor = 111;	# random number!
while($line=<DEVS>)
{
	foreach my $devname (@devnames)
	{
		if($line =~ /$devname/)
		{
			$devno = (split / /, $line)[0];
			print "Get devno:", $devno, "\n";
			$status = system("mknod $devname c $devno $devminor");
			$status = system("mv $devname /dev/$devname");
			$status = 1;
			last if $status;
		}
	}	
	last if $status;
}
close(DEVS);
# This is not the same like perl rules, it return a non-zero when failed!
#$oks = system("echo ok");
#print "Make status: $status, \n";
print "Make completely!" if $status; 
	
