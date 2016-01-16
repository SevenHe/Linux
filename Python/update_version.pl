#!/usr/bin/perl -w

use Tie::File;

tie my @contents, Tie::File, "client.py" or die "The client file have not been found.\n";
$version = $ARGV[0];
$lines = 0;

#$1 or $2 is just the group of the regex, it does not exist until the match was at the end.
for(@contents)
{
	$lines += 1 and print "Update version from $2 to $version.\n" if s/(JLU DrCOM Client - - Version) (\d[.]\d)/$1 $version/;
}
untie @contents;
print "Match lines: $lines.\n";

