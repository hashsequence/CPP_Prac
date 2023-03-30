# const placement

Const always applies to the left first, then the right. So

[1] const int

[2] int const

[3] const int*

[4] int* const

[5] int const *

[6] int const * const


1 and 2 are the same, they are both ints that can not change. 3 and 5 are also the same, they are pointers to an int that cannot change. 4 is a pointer that can not change to an int that can change. 6 is a pointer that can not change to an int that can not change.

The only time it really matters is when a type is made up of multiple parts (in this example, a type and a pointer to that type).
