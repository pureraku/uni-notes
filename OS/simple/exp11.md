# Experiment 11: LRU and LFU Page Replacement

## Aim
Compare Least Recently Used and Least Frequently Used replacement.

## Compile and run
`cc -std=c11 exp11.c -o exp11 && ./exp11`

Both algorithms use the same reference string and three frames. LRU evicts the least recently used page. LFU evicts the page with the lowest resident frequency; ties are broken by least recent use.
