package ScalarFile;

use Carp;
use strict;
use warnings;
use warnings::register;
my $count = 0;

sub TIESCALAR {
	my $class = shift;
	my $filename = shift;
	my $fh;
	if (open $fh, "<", $filename or open $fh, ">", $filename) {
		close $fh;
		$count++;
		return bless \$filename, $class;
	}
	carp "Can't tie $filename: $!" if warnings::enabled();
	return;
}

sub FETCH {
	my $self = shift;
	confess "I am not a class method" unless ref $self;
	return unless open my $fh, $$self;
	read($fh, my $value, -s $fh);
	return $value;
}

sub STORE {
	my ($self, $value) = @_;
	ref $self or confess "not a class method";
	open my $fh, ">", $$self or croak "can't clobber $$self:$!";
	syswrite($fh, $value) == length $value or croak "can't write to $$self: $!";
	close $fh or croak "can't close $$self:$!";
	return $value;
}

sub DESTORY {
	my $self = shift;
	confess "wrong type" unless ref $self;
	$count --;
}

1;
