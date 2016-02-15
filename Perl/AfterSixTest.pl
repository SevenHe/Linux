#!/usr/bin/perl

use warnings;

sub popmany {
	my @retlist = ();
	for my $aref(@_) {
		print "aref is '@$aref'!\n";
		push @retlist, pop @$aref;
	}

	return @retlist;
}

@a = (1, 3, 5, 7);
@b = (2, 4, 6, 8);
@c = (5, 6, 7, 8);
$d = \@c;
$e = [1, 2];							# "[]" is to create a reference, and it is a entirety.
@f = [6, 7, 8, 9];						# "{}" is to create a block.
$g = @a;
$h = [ @b ];

@tailings = popmany(\@a, \@b, \@c);		# equivalent to "\(@a, @b, @c)"!

for $i (0..$#a) {
	print "row $i is $a[$i].\n";
}

print "tailings is '@tailings'!\n";
print "OK!\n" if exists $d->[2]; 
print "[ $e ], g:$g, [ @f ], $a[1], $f[0], @$h\n";

%family = (
	johns => ["barney"],
	bestons => ["ok", "1fdafa3"],
	simpsons => ["sdfj", "654ok", "third"]
);
$family{"seven"} = ["inotok", "jd", "asf", "sdfe2"];

# sort {...}, the expression is the thing you want to compare, and the following is to compare the values 
# instead of the keys. 
for $member (sort { @{$family{$a}} <=> @{$family{$b}} } keys %family) {
	print "$member : @{$family{$member}} \n";
}

# use 'func (\[$@%])' to ensure the argument is what you specify, on the contrary, the 'func ([$@%])' is just 
# providing the program environment.

# class test!
# "->new()" is not equivalent to the "->new"!
use Person;
$test = Person->new(name => "test2");
$name = $test->get_name();
print "'test' name is $name!\n";
$name = $test->set_name("Lilei");
if ($name eq $test->get_name()) {
	print "Now, 'test' name is $name!\n";
}
