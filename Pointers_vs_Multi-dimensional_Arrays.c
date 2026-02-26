/*
 * Author: Tanmmoy Hasan Raju
 * Date: 2026-02-26
 * Time: 15:21
*/

//* Newcomers to C are sometimes confused about the difference between a two-dimensional
//* array and an array of pointers, such as name in the example above. Given the defini-
//* tions
//*     int a[10][20];
//*     int    *b[10];
//* then a[3][4] and b[3][4] are both syntactically legal references to a single int.

#include <stdio.h>

int main_I()
{
        int a[10][20];
        int x[20];
        int *b[10];

        a[3][4] = 100;
        b[3] = x;
        b[3][4] = 200;

        printf("a: %d *b: %d\n", a[3][4], b[3][4]);
        return 0;
}

//* But a is a true two-dimensional array: 200 int-sized locations have been set aside, and
//* the conventional rectangular subscript calculation 20 * row +col is used to find the
//* element a[row,col]. 
// How does 20 * row + column actually find a[row][column]?
// int a[10][20];
// This means:
// 10 rows
// 20 columns
// Total: 200 integers
// Stored in row-major order
// All memory is contiguous
// So in memory it looks like this:
// Row 0: a[0][0] a[0][1] ... a[0][19]
// Row 1: a[1][0] a[1][1] ... a[1][19]
// Row 2: a[2][0] a[2][1] ... a[2][19]
// ...
// hink of It as One Long 1D Array
// Physically in memory, it is equivalent to:
// int linear[200];
// Now we just need a formula that maps:
// (row, column) → linear index
// Each row has 20 elements.
// So to reach row, you must skip:
// row × 20 elements
// Then inside that row, move column steps.
// row * 20 + column
// That’s it.
// Find:
// a[3][4]
// Step 1: Skip full rows before row 3
// 3 rows × 20 elements = 60 elements
// Step 2: Move inside row
// + 4
// Total index:
// 60 + 4 = 64
// So a[3][4] is the 64th element (0-based) in the 200-element block.

//* For b, however, the definition only allocates 10 pointers and does not initialize them;
//* initialization must be done explicitly, either statically or with code. 
// If b is local (inside a function):
// int *b[10];
// Each element contains garbage addresses.
// So this is dangerous:
// b[3][4] = 10;
// Because:
// b[3] contains a random address
// b[3][4] tries to access memory relative to that garbage
// That’s undefined behavior.

// You must initialize each pointer.
// There are two ways.
// ️Static Initialization
// int row0[20], row1[20], row2[20];
// int *b[10] = { row0, row1, row2 };
// Now:
// b[0] → row0
// b[1] → row1
// b[2] → row2
// Now this works:
// b[1][4] = 100;
// Because:
// b[1] == row1
// And row1 has 20 integers.

// Dynamic Allocation
// Still not discussed, will be discussed soon!

//* Assuming that each element of b does point to a twenty-element array, then there will be
//* 200 ints set aside, plus ten cells for the pointers. 
// Suppose *p = x[20], then *p[10] will point to 10 x[20] = 20*10 = 200 + pointers 10

//* The important advantage of the pointer array is that the rows of the array may be of different
//* lengths. That is, each element of b need not point to a twenty-element vector; some may point
//* to two elements, some to fifty, and some to n  one at all.
// int a[10][20];
// Every row has exactly 20 elements.
// You cannot change that.
// Memory layout is fixed and rectangular.

// With pointer array
//      int *b[10];
// Now each b[i] is just a pointer.
// You can do:
// b[0] = malloc(2  * sizeof(int));   // 2 elements
// b[1] = malloc(50 * sizeof(int));   // 50 elements
// b[2] = malloc(1  * sizeof(int));   // 1 element
// b[3] = NULL;                       // no elements at all
// b[4] = malloc(n  * sizeof(int));   // dynamic size
// Now the rows are not equal length.
// This is called a jagged array (or ragged array).

// Why This Is Powerful
// Because now your structure can represent:
// Graph adjacency lists
// Variable-length strings
// Sparse matrices
// Dynamic tables
// Any structure where row sizes diffe
// A true 2D array cannot do that.

//* Although we have phrased this discussion in terms of integers, by far the most frequent use of
//* arrays of pointers is to store character strings of diverse lengths, as in the function
//* month_name. Compare the declaration and picture for an array of pointers:

// char *name[] = { "Illegal month", "Jan", "Feb", "Mar" };

// with those for a two-dimensional array:

// char aname[][15] = { "Illegal month", "Jan", "Feb", "Mar" };

// Array of Pointers to Strings
// char *name[] = { "Illegal month", "Jan", "Feb", "Mar" };

// What Is Allocated?
// Two things exist:

// The pointer array
// name[0]  name[1]  name[2]  name[3]
// Each element is a char *.
// The string literals
// Stored separately in static memory:

// "Illegal month"
// "Jan"
// "Feb"
// "Mar"

// Each string:
// Has its own exact length
// Stored once
// Automatically null-terminated

// Memory Picture (Conceptual)
// name
//  ├── → "Illegal month"
//  ├── → "Jan"
//  ├── → "Feb"
//  └── → "Mar"

// Each string is stored independently.

// Lengths:

// 13 chars + '\0'
// 3 chars + '\0'
// 3 chars + '\0'
// 3 chars + '\0'
// No wasted space.

// Two-Dimensional Character Array
// char aname[][15] = {
//     "Illegal month", "Jan", "Feb", "Mar"
// };

// Now something very different happens.
// What Is Allocated?
// One single contiguous block:
// 4 rows × 15 columns = 60 characters total

// Memory layout:
// Row 0: 15 chars
// Row 1: 15 chars
// Row 2: 15 chars
// Row 3: 15 chars

// Each row has exactly 15 characters reserved.

// Memory Picture
// aname
//  ├── ['I','l','l','e','g','a','l',' ','m','o','n','t','h','\0', ? ]
//  ├── ['J','a','n','\0', ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ]
//  ├── ['F','e','b','\0', ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ]
//  └── ['M','a','r','\0', ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? ]


// Notice:
// "Jan" uses 4 bytes
// But 15 bytes were reserved
// Remaining 11 bytes are unused
// Space is wasted.


// You should also check out the visual diagram representing the name pointer which points
// to variable length strings. And also the 2D representatio of this/