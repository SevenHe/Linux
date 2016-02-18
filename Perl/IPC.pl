#!/usr/bin/perl -w
use v5.6.0;
use strict;
use sigtrap qw(die INT TERM HUP QUIT);
my $PROGENY = shift(@ARGV) || 3;
eval { main() };
die if $@ && $@ !~ /^Caught a SIG/;
print "$@\nDone.\n";
exit;

sub main {
	my $mem = ShMem->alloc("Original Creation at" . localtime);
	my (@kids, $child);
	$SIG{CHLD} = 'IGNORE';
	for (my $unborn = $PROGENY; $unborn > 0; $unborn--) {
		if ($child = fork) {
			print "$$ begat $child\n";
			next;
		}
		die "cannot fork: $!" unless defined $child;
		eval {
			while (1) {
				$mem->lock();
				$mem->poke("$$ " . localtime) unless $mem->peek =~ /^$$\b/o;
				$mem->unlock();
			}
		};
		die if $@ && $@ !~ /^Caught a SIG/;
		exit;	# the child process exits!
	}

	while (1) {
		print "Buffer is ", $mem->get, "\n";
		sleep 1;
	}
}

package ShMem;

use IPC::SysV qw(IPC_PRIVATE IPC_RMID IPC_CREAT S_IRWXU);
use IPC::Semaphore;
sub MAXBUF() { 2000 }

sub alloc {
	my $class = shift;
	my $value = @_ ? shift : ' ';
	my $key = shmget(IPC_PRIVATE, MAXBUF, S_IRWXU) or die "shmget: $!";
	my $sem = IPC::Semaphore->new(IPC_PRIVATE, 1, S_IRWXU | IPC_CREAT)
		or die "IPC::Semaphore->new: $!";
	$sem->setval(0, 1) or die "sem setval: $!";
	my $self = bless {
		OWNER => $$,
		SHMKEY => $key,
		SEMA => $sem,
	} => $class;

	$self->put($value);
	return $self;
}

sub get {
	my $self = shift;
	$self->lock;
	my $value = $self->peek(@_);
	$self->unlock;
	return $value;
}

sub peek {
	my $self = shift;
	shmread($self->{SHMKEY}, my $buff=' ', 0, MAXBUF) or die "shmread: $!";
	substr($buff, index($buff, "\0")) = ' ';
	return $buff;
}

sub put {
	my $self = shift;
	$self->lock;
	$self->poke(@_);
	$self->unlock;
}

sub poke {
	my ($self, $msg) = @_;
	shmwrite($self->{SHMKEY}, $msg, 0, MAXBUF) or die "shmwrite: $!";
}

sub lock {
	my $self = shift;
	$self->{SEMA}->op(0, -1, 0) or die "semop: $!";
}

sub unlock {
	my $self = shift;
	$self->{SEMA}->op(0, 1, 0) or die "semop: $!";
}

sub DESTROY {
	my $self = shift;
	return unless $self->{OWNER} == $$;
	shmctl($self->{SHMKEY}, IPC_RMID, 0) or warn "shmctl RMID: $!";
	$self->{SEMA}->remove() or warn "sema->remove: $!";
}
