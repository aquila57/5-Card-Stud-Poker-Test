#!/bin/bash
if [ -z $1 ]
then
echo "5 Card Stud Poker Test"
echo "Dieharder random number generators"
echo "Usage: $0 Dieharder_RNG_number"
echo "Example: $0 053"
echo "To get a list of dieharder generators, type:"
echo "dieharder -g -l"
exit 1
fi
dieharder -g $1 -t 1000000 -o | diestud $1
