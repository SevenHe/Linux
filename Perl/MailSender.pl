#!/usr/bin/perl

use Net::SMTP::SSL;

use strict;
use warnings;

our $smtp = Net::SMTP::SSL->new("smtp.qq.com", Port => 465) or die "Failed to connect to the SMTP server!";

sub addAuthor {
	$smtp->auth('961950442@qq.com', 'Seven1001');
	$smtp->mail('961950442@qq.com');
	$smtp->to('2307849251@qq.com', '961950442@qq.com');
}

sub sendMail {
	#Start the mail
	$smtp->data();

	#Edit the header
	$smtp->datasend("To: 2307849251\@qq.com\n");
	$smtp->datasend("From: 961950442\@qq.com\n");
	$smtp->datasend("Subject: Send from perl to test.\n");

	#Separate the header from the body
	$smtp->datasend("\n");

	# Send the body.
	$smtp->datasend("I love you, indigo!\n");
	$smtp->datasend("Seven...\n");

	# Finish sending the mail
	$smtp->dataend(""); 

	# Close the SMTP connection
	$smtp->quit();
	
	# $?-- is for the command status outside the perl compiler.
	# so don't return the $?.
}

#print addAuthor(), "\n";
#print sendMail(), "\n";

if(addAuthor() && sendMail()) {
	print "Email is sending...\n";
}
else {
	print "Error in the last step";
}
	