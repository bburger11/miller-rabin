# miller-rabin

This is a C program that performs the Miller Rabin primality test. Miller Rabin is a modular arithmetic based algorithm to determine whether an inputted odd number is composite or probably. This demonstrates a form of probabilistic compting. Usage is as follows:

```
usage: miller-rabin -n NUM -k ROUNDS
    NUM    - odd integer to be tested
    ROUNDS - number of rounds of testing
```

## How to run

Clone this repository.

Compile the `miller-rabin` binary by running `make`.

Follow instructions from usage above to run a single test or run the premade tests by using the bash script, `run-tests.sh`.

The test script will test 10 composites and 10 primes from `composites.csv` and `primes.csv`, in that order. Miller Rabin will successfully identify all of these numbers as "composite" and "probably prime" respectively.

## Math Background

### Fermat's Little Theorem

If n is prime, then for any a, we have <a href="https://www.codecogs.com/eqnedit.php?latex=a^{n-1}&space;=&space;1&space;(mod&space;n)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?a^{n-1}&space;=&space;1&space;(mod&space;n)" title="a^{n-1} = 1 (mod n)" /></a>.
This suggests the Fermat test: pick a random <a href="https://www.codecogs.com/eqnedit.php?latex=a&space;\in&space;[1..n-1]" target="_blank"><img src="https://latex.codecogs.com/gif.latex?a&space;\in&space;[1..n-1]" title="a \in [1..n-1]" /></a> and see if <a href="https://www.codecogs.com/eqnedit.php?latex=a^{n-1}&space;=&space;1&space;(mod&space;n)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?a^{n-1}&space;=&space;1&space;(mod&space;n)" title="a^{n-1} = 1 (mod n)" /></a>. holds

### Miller Rabin Theorem

We recall that n is prime if and only if the solutions of <a href="https://www.codecogs.com/eqnedit.php?latex=x^2&space;=&space;1&space;(mod&space;n)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?x^2&space;=&space;1&space;(mod&space;n)" title="x^2 = 1 (mod n)" /></a> are <a href="https://www.codecogs.com/eqnedit.php?latex=x&space;=&space;\pm&space;1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?x&space;=&space;\pm&space;1" title="x = \pm 1" /></a>.
If n passes the Fermat test, we should also check <a href="https://www.codecogs.com/eqnedit.php?latex=a^{(n-1)/2}&space;=&space;\pm&space;1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?a^{(n-1)/2}&space;=&space;\pm&space;1" title="a^{(n-1)/2} = \pm 1" /></a>.
Similarly, the Miller-Rabin test picks a random <a href="https://www.codecogs.com/eqnedit.php?latex=a&space;\in&space;[1..n-1]" target="_blank"><img src="https://latex.codecogs.com/gif.latex?a&space;\in&space;[1..n-1]" title="a \in [1..n-1]" /></a> and determines if these equalities hold.

### Performance

For any composite n, the probability that n will pass the Miller-Rabin test is at most ¼, and thus Miller-Rabin will correctly identify a composite with at least ¾ probability.

## Methodology Summary

#### Test Primality
- Checks base cases, calls the Miller-Rabin test k times.

#### Miller-Rabin
- Chooses a random a value, performs Miller-Rabin test.

#### Power
- Modular exponentiation utility function.
