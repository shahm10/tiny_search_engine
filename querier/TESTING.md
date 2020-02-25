# CS50 Lab 6
## Seung Hyun Hahm, CS50 Winter 2020

### TESTING 
The testing for querier can be found in `testing.sh`

In `testing.sh`, I test the cases described in Testing plan in [DESIGN.md]()

The output of `testing.sh` can be found in `testing.out`

In order to access this, type `make test &> testing.out`

### Additional Information & Assumption 

Because `seedURL` wiki takes a long time to load, I only tested with a seedURL used in the course webpage and compared the result with the results provided in the courses webpage. Also, inside the `incorrectsyntax` file, I added few more test cases for spaces, non-alphabets, and captialization. 

For this test, assume inside the `tiny-search-engine-shahm10`, a directory data/letters are created and there, the `pageDirectory` and the `indexFile` are all stored inside. 

### Memory Leak

Below are the sample valgrind output for `./querier ../data/letters ../data/index_letters < incorrectsyntax` 

```c
==2916735== HEAP SUMMARY:
==2916735==     in use at exit: 0 bytes in 0 blocks
==2916735==   total heap usage: 969 allocs, 969 frees, 79,867 bytes allocated
==2916735== 
==2916735== All heap blocks were freed -- no leaks are possible
==2916735== 
==2916735== For lists of detected and suppressed errors, rerun with: -s
==2916735== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


```
Another sample valgrind output for `./querier ../data/letters ../data/index_letters < testfile` 

```c
==2916724== HEAP SUMMARY:
==2916724==     in use at exit: 0 bytes in 0 blocks
==2916724==   total heap usage: 1,137 allocs, 1,137 frees, 276,049 bytes allocated
==2916724== 
==2916724== All heap blocks were freed -- no leaks are possible
==2916724== 
==2916724== For lists of detected and suppressed errors, rerun with: -s
==2916724== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```

