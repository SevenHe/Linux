#!perl -w
# visual->Shift+G->=, more conciser way, == !
# m is move line to!!
use English;

# $1 , $2 and.. is only for match use.
# the $ARG is the argument which is read from the <DATA> flow.
sub check_one {
		my $re = shift;
		print "ARG = $ARG\n";
		print "$ARG =~ $re \n";
# for test.		if ('hjik hjik' =~ m/(\w+)\s*\1/) { print "ok\n"; }
#=begin comment
		if ($ARG =~ $re)	
		{	
			if ($1) 
			{
				print " matches: '$MATCH' ('$`', '$'', '$1')\n";
			}
			else
			{
				print " Matches: $&--($`, $')\n";
			}
		}	
		else	
		{	
				print " doesn't match\n";
		}	
#=cut	
}

# the __END__ to indicate the perl program is finished, and simulate a standard input.
while (<DATA>)
{
		chomp;
		check_one('[a-z]');
		check_one('(\W+)');
		check_one('\W*');
		check_one('^\w+$');
		check_one('[^\w+$]');
		check_one('\d');
		check_one('(.+)\s*\1'); # \1...a sub match pattern, at the fore of the position where \1 executes.
		check_one('((.+)\s*\1)');
		check_one('(.+)\s*((\1))');
		check_one('\DOS');
		check_one('\\DOS');
		check_one('\\\DOS');
}
__END__
the quick brown fox jumped over the lazy dog
The Sea! The Sea!
(.+)\s*\1
9780471975632
C:\DOS\PATH\NAME
