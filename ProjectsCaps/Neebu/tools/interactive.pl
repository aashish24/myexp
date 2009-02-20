#!/usr/bin/perl -w

$| = 1;		# autoflush output

use strict;
use IO::Socket;
my ( $port, $handle, $reply );
my ( $token, @values, $v, $input_line );


print "\n\ntcp testing shell\n-----------------\n\n> ";
while ( $input_line = <STDIN> ) {

    if ( $input_line =~ /^$/ ) {
        print "> ";
        next;
    }

    chomp( $input_line );

    ( @values ) = split( / /, $input_line );
    foreach $v ( @values ) { $v =~ s/\s//g; }
    $token = shift( @values );


    if ( $token =~ /open/i ) { 
        print "\n--attempting to open connection to $values[0] on port $values[1]...\n";

        # create a tcp connection to the specified host and port
        $handle = IO::Socket::INET->new( Proto     => "tcp",
                                         PeerAddr  => $values[0],
                                         PeerPort  => $values[1] )
            or die "can't connect to port $values[1] on $values[0]: $!";

        $handle->autoflush(1);              # so output gets there right away

        print STDERR "\tclient [$0] connected to host [$values[0]] on port [$values[1]]\n";
        print <$handle>;
    }
    elsif ( $token =~ /shutdown/i ) {
        print "\nsending command [shutdown]...\n";
        print $handle "shutdown\n";
        $reply = <$handle>;
        chomp( $reply );
        print "\t...reply is [$reply]\n";
        close $handle;
        last;
    }
    elsif ( $token =~ /quit/i ) {
        print "\ndone\n\n";
        last;
    }
    elsif ( $token =~ /help/i ) {
        print "\ntcp testing shell commands:\n\n";
        print "\topen <hostname> <port> - tries to open host:port\n";
        print "\tclose                  - close connection\n";
        print "\tshutdown               - sends -shutdown- to server and quits\n";
        print "\tquit                   - quits this shell\n";
        print "\n\n";
    }
    else {
        print "\nsending command [$token]...\n";

        print $handle $token;
        #foreach $v ( @values ) { print $handle " ".$v }
        #print $handle "\n";

        $reply = <$handle>;
        chomp( $reply );
        print "\t...reply is [$reply]\n";
    }

    print "> ";
}


1;






