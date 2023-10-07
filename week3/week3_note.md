# Lecture 3 - Algorithms
### Search Algorithms
- Linear search (tuyến tính)
- Binary search (nhị phân)

---
### Running time - big O notation 
![time to solve](https://cs50.harvard.edu/x/2023/notes/3/cs50Week3Slide042.png) \
*Order of running time (the worst - the fastest)*
1. O(n<sup>2</sup>) - the worst
2. O(n) - linear search 
3. O(log n) - binary search
4. O(1) - the fastest 
---
### Linear Search - Examples 
<font color="green">**search-string**</font>
- `segmentation fault` - where a part of memory was touched by your program that is should not have access to
- `what do they mean "return 0 - return 1", why do we put it there ?` => if we don't put return, the loop is still running.
- `why return 0 or return 1 ?` => "return 0" - means the code is done. "return 1" - means the code is quite done (such as it's done but it didn't really find what I was looking for)
--- 
### Data Structures 
<font color="green">**Create your own data types**</font>
> typedef struct\
>{\
>   &nbsp;&nbsp;&nbsp;&nbsp;string name;\
>   &nbsp;&nbsp;&nbsp;&nbsp;string number;\
>}\
> person;
- `typedef` - define your own type
- `struct` - structure that has multiple values inside 
- `person` - name of the data type\ 
---
### Sorting
<font color="green">**Selection sort**</font>
>for i from 0 to n-1\
>&nbsp;&nbsp;&nbsp;&nbsp;find smallest number in the range of [i, n-1]\
>&nbsp;&nbsp;&nbsp;&nbsp;swap smallest number with number[i]

<font color="green">**Buble Sort**</font>
>Repeat n-1 times\
>&nbsp;&nbsp;&nbsp;&nbsp;for i from 0 to n-2\
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if number[i] & number[i+1] out of order\
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;swap them 
---
### Recursion
A function to call itself.\
