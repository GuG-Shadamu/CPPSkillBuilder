# const


## const variables


- A **compile time constraint**  that an object cannot be modified 

```cpp

const int i = 9;

const int *p1 = &i; // Data is const, pointer is not

int* const p2; // pointer is const, data is not 

const int* const p3; // both const

int const *p4 =  &i; // data is const, pointer is not
const int *p4 =  &i; // data is const, pointer is not

```

- if const is on the left of *, data is const
- if const is on the right of *, pointer is const

```cpp
const int i = 9;
const_cast<int&>(i) = 6;

// cast away the const of i

int j;
static_cast<const int&>(j);
// cast a data into const

```

- avoid cast to/away const

### pro

- const means the variable can be put in ROM (read only memory)
- enables compiler to do optimizeation



## Const in Function

- when a function is const and we want to change, say a recording value, we can mark that value as mutable