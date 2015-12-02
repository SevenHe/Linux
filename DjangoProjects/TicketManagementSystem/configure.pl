#!/usr/bin/perl -w
# -w measn 'use  warnings'
# a simple script to configure nginx.
# @ARGV is the command-line variable, @ARG is used in a subroutine to set the default array!
# a example to change mode:
=begin comment
	$mode = (stat("./filename"))[2];
	printf "%04o\n", ($mode & 007777);
=cut
# @ARGV = qw/ 1.conf /;
# $^I = ".bak"/""; # this $^I is suitable for the simple file changing circs, because passing arguments will be forced to use it.
# if do not use $^I, use 'print FILE STRING', to add to the file.(But this is not the simplest), so
use Tie::File;

=begin old_method
	open(CONF, "+<$ARGV[0]") or die "This configuration file is not valid.";
=cut

tie my @contents, "Tie::File", "$ARGV[0]" or die "This config file is not valid!!\n";
$option = $ARGV[1]; 
# This time, ARGV is a scalar. @ is better to use when the variable is an array rather than a scalar!!
$result = 0;
@dirs = ("static", "media");
OUT:for(@contents)
{
	# 'eq'  is used for comparing strings. '\b' is just a boundary.
	if($option eq 'HW')
	{
	IN1:foreach my $dir (@dirs)
		{
			$result += 1 and print "Have disabled old $dir config.\n" if s/^(\s*\balias\b.*TicketManagementSystem\/$dir.*)/#$1/;
			$result += 1 and print "Have enabled new $dir config.\n" if s/^#(\s*\balias\b.*HelloWorld\/$dir.*)/$1/;
			next IN1 if $dir eq "media";
		}
		next OUT;
	}
	elsif($option eq 'TMS')
	{
	IN2:foreach my $dir (@dirs)
		{
			$result += 1 and print "Have disabled old $dir config.\n" if s/^#(\s*\balias\b.*TicketManagementSystem\/$dir.*)/$1/;
			$result += 1 and print "Have enabled new $dir config.\n" if s/^(\s*\balias\b.*HelloWorld\/$dir.*)/#$1/;
			next IN2 if $dir eq "media";
		}
		next OUT;
	}
}
untie @contents;
if($result == 0)
{
	print "The file has been configured!\n";
}
elsif($result >= 1 && $result < 4)
{
	print "Thera are some problems in the file to be configured..\n";
}
else
{
	print "Configuration is successful!!\n";
}
