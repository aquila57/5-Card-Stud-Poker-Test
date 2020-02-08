#!/bin/bash
if [ -z $1 ]
then
echo "5 Card Stud Poker Test with GNU Scientific Library"
echo "random number generators"
echo "Usage: $0 generator"
echo "Example: $0 taus2"
echo "Example: $0 mt19937"
echo "Example: $0 ranlxd2"
echo "For a list of GSL generators, type:"
echo "$0 ?"
exit 1
fi
GSL_RNG_TYPE="$1"
export GSL_RNG_TYPE
gslstud
