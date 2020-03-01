# Lab 6 Grader Sheet

### Student: Seung Hyun Hahm
### Grader: Katie Huang

****

## Delivery
10/10

## Makefiles
12/12

## Documentation
12/12

## Testing
6/6

## Style
17/20

-3, functionality of `querier` is written in `main`; `querier` should be in a separate function and `main` should only parse arguments

## Functionality
38/40

-2, seg fault occurs when a query is empty

```
==3997== Invalid read of size 1
==3997==    at 0x4C2F1B1: strcmp (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==3997==    by 0x401C00: andorcheck (querier.c:277)
==3997==    by 0x40156B: main (querier.c:125)
==3997==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
```

## Overall

Comments: None.

Total: 95/100

Amazing job!