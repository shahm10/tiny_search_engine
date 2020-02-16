# CS50 Lab 5
## Seung Hyun Hahm, CS50 Winter 2020

### TESTING 
The testing for indexer and indextest can be found in `testing.sh`

In `testing.sh`, I test the cases described in Testing plan in [DESIGN.md]()

The output of `testing.sh` can be found in `testing.out`

In order to access this, type `make test &> testing.out`

### Additional Information

Because there is an assumption that when files are created from index through `index_load` the order does not matter, in order to test if two indexfiles are same, I had to use `indexsort.awk`

### Two created indexfiles

These can be accessed under `newindexfile.sorted` and `oldindexfile.sorted`
The ouput is given below
The rest, please check `testing.out`

```c
newindexfile.sorted
algorithm 2 1 
biology 6 1 
breadth 3 1 
computational 6 1 
depth 5 1 
eniac 4 1 
first 3 1 5 1 
home 1 2 2 1 3 1 4 1 5 1 6 1 
page 1 1 
playground 1 1 
search 3 1 5 1 
this 1 1 

oldindexfile.sorted
algorithm 2 1 
biology 6 1 
breadth 3 1 
computational 6 1 
depth 5 1 
eniac 4 1 
first 3 1 5 1 
home 1 2 2 1 3 1 4 1 5 1 6 1 
page 1 1 
playground 1 1 
search 3 1 5 1 
this 1 1 

```
### Memory leak
All items are freed

```c
==3233285== HEAP SUMMARY:
==3233285==     in use at exit: 0 bytes in 0 blocks
==3233285==   total heap usage: 1,165 allocs, 1,165 frees, 148,316 bytes allocated
==3233285== 
==3233285== All heap blocks were freed -- no leaks are possible
==3233285== 
==3233285== For lists of detected and suppressed errors, rerun with: -s
==3233285== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==3233294== Memcheck, a memory error detector
==3233294== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==3233294== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==3233294== Command: ./indextest oldindexfile newindexfile
==3233294== 
==3233294== 
==3233294== HEAP SUMMARY:
==3233294==     in use at exit: 0 bytes in 0 blocks
==3233294==   total heap usage: 575 allocs, 575 frees, 27,224 bytes allocated
==3233294== 
==3233294== All heap blocks were freed -- no leaks are possible
==3233294== 
==3233294== For lists of detected and suppressed errors, rerun with: -s
==3233294== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```


