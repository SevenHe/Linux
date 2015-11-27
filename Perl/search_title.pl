#!/usr/bin/perl
# To match the titles that you specified.
open(ENCRYPTED, "<-") or die print("Open stdin pipe failed!");
while(<ENCRYPTED>)
{
	($code = $_) =~ tr/a-zA-Z0-9/n-za-mN-ZA-M4-90-3/;
	print $code;
}
