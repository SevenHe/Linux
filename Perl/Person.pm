#!/usr/bin/perl
package Person;

use warnings;

sub new {
	my $class = shift;
	# @_ is for the input arguments to cover the defaults!!
	my $self = { 
		name => "test",
   		sex  => "female",
		@_,
	};
	bless($self, ref $class || $class);
	return $self;
}

sub set_name {
	my ($self, $name) = @_;
	print "The name is $self->{name} in the set_name process!\n";
	$self->{name} = $name;
	return $self->{name}; 
}
# shift action just gets one argument, as a hash, we should use @_, and @_ is just a piece of memory, showing as a string!
# And there must be a "()" to surround the variable, because it is a entirety as a hash!!!
# Remember, it's very important!
sub get_name {
	my ($self) = @_;
	my $judgement = ref @_;					
	# This is the proof to ensure it is not a reference, just save datum.
	# print "The default is $self, $judgement!\n";
	print "The hash is $self->{name}, $self->{sex}!!\n";
	return $self->{name};
}

1;	# To ensure the package return a ture value!
