#!/usr/bin/perl -w

use Thread 'async';

$t1 = async {
	my $stuff = getpwuid($>);
	return $stuff;
};

$t2 = async {
	my $motd = `echo "This is ok"`;
	return $motd;
};

@retlist = $t1->join();
$retval = $t2->join();

print "1st kid returned @retlist\n";
print "2nd kid returned $retval\n";

