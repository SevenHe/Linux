#!/usr/bin/perl
# use strict;

use Data::Dumper;
use warnings;

print "Enter a number:";
chop($num = <STDIN>);
print $num + 1, "\n";
$test1 = 123;
$test2 = 3;
print $test1 x $test2, "\n";
print "$num is not $test1 and $test2. \n";
$test3 = 2;
$test3 .= $test2;
print "$test3 \n";

#All these obey the rules.
#"&&", the last one that meets the condition;"||", however the first one.
print $test3 <= 3 || $test3 + 1 . "\n";

#"or" or "and", just print the first string.
#print "Print $test3.\n" or "Test1 is not equal to 1. \n";

#Don't appear anything.
#print $test3 <= 3 and "Test3 = $test3. \n";

open(LOG, "records.log") or die "Can't open the file records.log:$!.\n";

print $test2 <=> $test3, "\n";

($good, $bad, $ugly) = split(/,/, "vi,emacs,teco");
print "$good $bad $ugly \n";
#Use the default settings to make the code pithy.
while(<LOG>) {
	print if /Average/;
}

$hashTest = {
		  'H' => 1,
		  'a' => 2,
		  's' => 3,
		  'h' => 4
		    };
print Dumper($hashTest);

#Test' $" ', represent the values in the array. 
#{}--lead to every variable as a Hash!
#@array = {$test1, $test2, $test3};
#$len = @array, the scalar is just the len of the @array!
@array = ($test1, $test2, $test3);
my $testArray = join($", @array);
print $testArray;
print Dumper($testArray);

# use ` ` to indicate the following string to file handle is a glob of commands.
# But the after-effect is lines' color behind this line would not change!

# the usage of "<<[identifier]["" x times]", the last line must be "identifier" without anything else.
print <<EOC;
echo lo there
EOC

# "<", input association; ">", output association!(Relevance)
open(ACCESS, "<access.log")  or die "Can't open the access.log.";
while(<ACCESS>) {
	print $_ . "\n";
}
open(TEST, "<-") or die "Can't input by using STDIN.";
while(<TEST>) {
	print if /my/;
	last if /end/;
}

# match patterns
$rotate13 = 'abcc4a8z';
$rotate13 =~ tr/a-zA-Z/n-za-mN-ZA-M/;  # work by offset
print $rotate13;
