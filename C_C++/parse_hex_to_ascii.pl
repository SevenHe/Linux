#!/usr/bin/perl -w

open(FH, '<sock_hex_data.dt') or die "open file error: $!";
# always as a scalar
while($line=<FH>)
{
	@hexs = split " ", $line;
	print @hexs;
	foreach my $hex (@hexs)
	{
		print chr(hex($hex)), ' ';
	}
}
