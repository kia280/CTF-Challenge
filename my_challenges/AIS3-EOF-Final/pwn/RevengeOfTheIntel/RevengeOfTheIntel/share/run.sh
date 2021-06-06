#!/bin/bash

proof_of_work () {
	difficulty=26
	prefix=$(cat /dev/urandom | tr -dc 'a-z0-9' | fold -w 8 | head -n 1)
	echo
	echo "This challenge is rate-limited."
	echo "In order to access the challenge, you must solve the Proof of Work."
	echo "You can use the following command:"
	echo
	echo "hashcash -mb$difficulty $prefix"
	echo
	echo "To install Hashcash, you can use the following command within Ubuntu:"
	echo
	echo "apt install hashcash"
	echo
	echo -n "your hashcash stamp: "
	read stamp
	if ! /usr/bin/hashcash "-cdb$difficulty" -r "$prefix" "$stamp" ; then
		exit
	fi
}

#proof_of_work
#cd /home/RevengeOfTheIntel
./sde/sde64 -debug -cet -cet-stderr -no-follow-child -- ./chal
