#!/usr/bin/env bash

composites="./composites.csv"
primes="./primes.csv"

echo "Testing composites..."
while read line 
do
    echo "Testing $line"
    echo $(./miller-rabin -n $line -k 1)
done < "$composites"

echo "Testing primes..."
while read line 
do
    echo "Testing $line"
    echo $(./miller-rabin -n $line -k 1)
done < "$primes"
