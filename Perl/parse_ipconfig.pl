#!/usr/bin/perl
# This is my first time to use Perl, i used to use Python.
# base on the "ipconfig".
use strict;
use Sys::HostAddr;
use Data::Dumper;

sub ipconfig {
	my $sys_addr = Sys::HostAddr->new();
	my $ip_addr = $sys_addr->ip();
	return $ip_addr;
}
print Dumper(ipconfig);