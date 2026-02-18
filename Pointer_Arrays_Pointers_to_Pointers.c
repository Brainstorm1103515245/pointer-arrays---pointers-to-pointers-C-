/*
 * Author: Tanmmoy Hasan Raju
 * Date: 2025-11-07
 * Time: 23:14
*/
#include <stdio.h>
//* Since pointers are variables themselves, they can be stored in arrays just as other
//* variables can.

// 1. Array of int pointers-
int main_()
{
        int a = 10, b = 20, c = 30;
        int *arr[3];
        arr[0] = &a;
        arr[1] = &b;
        arr[2] = &c;
        for (int i = 0; i < 3; i++) {
                printf("%d\n", *arr[i]);
        }
        return 0;
}
// 2. Array of char ponters-
int main__()
{
        char *names[] = {"Alice", "Bob", "Charlie"};
        for (int i = 0; i < 3; i++)
                printf("%s\n", names[i]);
        return 0;
}

//* Let us illustrate by writing a program that will sort a set of text lines into
//* alphabetic order, a stripped-down version of the UNIX program sort.
// In this section, K&R move beyond simple pointer and array relationships and use
// them in a real-world example:
// a program that reads a collection of lines, stores them, and then sorts them
// alphabetically using pointers rather than copying entire strings around.

//* In Chapter 3, we presented a Shell sort function that would sort an array of
//* integers, and in Chapter 4 we improved on it with a quicksort. The same algor-
//* ithms will work, except that now we have to deal with lines of text, which are
//* of different lengths, and which, unlike integers, can't be compared or moved in
//* a single operation. We need a data representation that will cope efficiently and
//* conveniently with variable-length text lines.
// This passage introduces the motivation for using pointers to pointers in the “sort”
// example that follows. K&R are saying:
// -Earlier, sorting integers was simple — each element was a fixed-size number, so
//  comparisons and swaps were straightforward.
// -But now, each line of text has a different length, and copying them around (moving
// whole strings) would be inefficient.
// -Therefore, instead of storing and moving the text itself, we can store and manipulate
//  pointers to those strings.

//* This is where the array of pointers enters. If the lines to be sorted are stored
//* end-to-end in one long character array, then each line can be accessed by a pointer
//* to its first character.
// Imagine you have a single large character array, something like:
// +--------------------------------------------------------+
// | H e l l o \n W o r l d \n C o d i n g \n ...           |
// +--------------------------------------------------------+
//   ^         ^             ^
//   |         |             |
//  line 1     line 2        line 3
// All the input lines are written back-to-back into one continuous buffer.
//* The pointers themselves can be stored in an array. Two lines can be compared by passing
//* their pointers to strcmp. When two out-of-order lines have to be exchanged, the pointers
//* in the pointer array are exchanged, not the text lines themselves.
// “The pointers themselves can be stored in an array.” <-- this is crucial line
// char *lineptr[MAXLINES];
// This is an array of pointers to char.
// Each element points to the beginning of one line:
// lineptr[0] → "Hello"
// lineptr[1] → "World"
// lineptr[2] → "Apple"
// lineptr[3] → "Zebra"
// The actual text remains in the big character buffer, untouched.

// “Two lines can be compared by passing their pointers to strcmp.”
// This is important.
// Since each line is represented by a pointer to its first character, comparing two
// lines is as simple as:
// strcmp(lineptr[i], lineptr[j])
// lineptr[i] → pointer to the first character of line i
// lineptr[j] → pointer to the first character of line j
// strcmp walks along each string and returns:
// negative if line i < line j (alphabetically)
// positive if line i > line j
// zero if equal
// This avoids copying any text — we’re comparing through the pointers.

// “When two out-of-order lines have to be exchanged, the pointers in the pointer array
// are exchanged, not the text lines themselves.”
// This is the most important idea.
// Suppose the sorting algorithm finds two lines in the wrong order.
// Instead of doing this (very expensive):
// swap entire strings in memory
// We do the cheap version:
// temp = lineptr[i];
// lineptr[i] = lineptr[j];
// lineptr[j] = temp;
// This swaps only the pointers, not the text they point to.

//* This eliminates the twin problems of complicated storage management and high overhead
//* that would go with moving the lines themselves.
// “This eliminates the twin problems…”
// They mean these two problems:

// Problem 1: Complicated storage management
// If you tried to physically move the text lines during sorting, you would have to:
// Allocate new memory for each line
// Copy the entire string into new locations
// Free the old memory
// Keep track of all these allocations
// Handle different line lengths
// Potentially shift many characters around
// This becomes very messy and easy to break.
// With pointers:
// You skip all that.
// You just store the text once, in one big array (simple).
// You never move the text.
// You never need to reallocate or free memory for every swap.
// No complicated memory management needed.
// Just pointer swaps.

// Problem 2: High overhead (slow) of moving the lines themselves
// Imagine two long strings:
// "InternationalProgrammingCompetition"
// "Algorithm"
// If you sort by moving the entire strings:
// You must copy every character.
// That expensive copying happens many times in sorting.
// This is high overhead.
// With pointers:
// A swap is just:
// char *tmp = lineptr[i];
// lineptr[i] = lineptr[j];
// lineptr[j] = tmp;
// That’s a few bytes.
// Instant.
// No copying.
// Zero overhead.

//* The sorting process has three steps:
//*     read all the lines of input
//*     sort them
//*     print them in order

//* As usual, it's best to divide the program into functions that match this natural
//* division, with the main routine controlling the other functions. Let us defer the
//* sorting step for a moment, and concentrate on the data structure and the input and
//* output.
// In this section, K&R explain that before implementing the sorting
// algorithm, it is best to design the program around the natural
// structure of the problem. The program is divided into separate
// functions, each handling one clear task. The main routine simply
// coordinates these tasks. At this point, we temporarily ignore the
// sorting step and focus instead on the foundation: how the lines
// will be stored, how the input will be read, and how the output will
// be written. Storing text lines efficiently is important because each
// line can have a different length, and directly moving whole text
// strings during sorting would be slow and complicated. To solve this,
// the program uses an array of pointers: all text lines are stored
// sequentially in one large character buffer, and an array of `char *`
// pointers keeps track of where each line starts. This design allows
// the sorting function to rearrange only the pointers instead of the
// text itself, avoiding both complicated memory management and the high
// overhead of copying long strings. Once this data structure and the
// input/output routines are in place, adding the sorting algorithm
// becomes straightforward, since it merely reorders the pointers.
// This separation of concerns—data structure first, algorithm later—
// produces a clean, efficient, and maintainable program.

//* The input routine has to collect and save the characters of each line, and build an
//* array of pointers to the lines. It will also have to count the number of input lines,
//* since that information is needed for sorting and printing. Since the input function
//* can only cope with a finite number of input lines, it can return some illegal count
//* like -1 if too much input is presented.
// The input routine is responsible for reading each line of text from
// the user, saving the characters of each line in memory, and creating
// an array of pointers so that each pointer refers to the beginning of
// one line. As it reads the text, the function must also keep track of
// how many lines have been successfully stored, because this count will
// later be needed by the sorting and printing routines. Since the
// program can only store a limited number of lines (based on the size
// of the pointer array and the available buffer space), the input
// function must detect when the input exceeds these limits. If too many
// lines are presented or if the buffer fills up, the routine cannot
// store the additional data, so it signals an error by returning an
// illegal count such as -1. This gives the rest of the program a clear
// indication that the input could not be processed fully.

//* The output routine only has to print the lines in the order in which they appear in
//* the array of pointers.

//--------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>

#define MAXLINE 5000    /* max lines to be stored */

char *lineptr[MAXLINE];         /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main()
{
        int nlines;     /* number of input lines read */

        if ((nlines = readlines(lineptr, MAXLINE)) >= 0) {
                qsort(lineptr, 0, nlines-1);
                writelines(lineptr, nlines);
                return 0;
        } else {
                printf("input too big to sort\n\a");
                return 1;
        }
}

#define MAXLEN 1000     /* max length of any input lines */
int get_line(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
        int len, nlines;
        char *p, line[MAXLEN];

        nlines = 0;
        while ((len = get_line(line, MAXLEN)) > 0) {
                if (nlines >= MAXLINE || (p = alloc(len)) == NULL)
                        return -1;
                else {
                        line[len-1] = '\0';
                        strcpy(p, line);
                        lineptr[nlines++] = p;
                }
        }
        return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
        int i;

        for (int i = 0; i < nlines; i++)
                printf("%s\n", lineptr[i]);
}

#define ALLOCSIZE 3000
#define BARWIDTH  70

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

void print_pbar(void)
{
    int used = allocp - allocbuf;
    int total = ALLOCSIZE;

    int width = (used * BARWIDTH)/total;

    for (int i = 0; i < BARWIDTH; i++) {
        if (i < width)
            printf("#");
        else
            printf(".");
    }
    printf("Space left: [%d%%]", 100 - (used*100)/total);
    printf("\n");
}

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        print_pbar();
        return allocp - n;
    } else
        return 0;

}

void afree(char *p)
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
    print_pbar();
}

void qsort(char *v[], int left, int right)
{
        int i, last;
        void swap(char *v[], int i, int j);

        if (left >= right) /* do nothing if array contains */ return;	/* fewer than two elements */
        swap(v, left, (left + right)/2); last = left;
        for (i = left+1; i <= right; i++)
                if (strcmp(v[i], v[left]) < 0)
                        swap(v, ++last, i);
        swap(v, left, last);
        qsort(v, left, last-1);
        qsort(v, last+1, right);
}
void swap(char *v[], int i, int j)
{
        char *temp;
        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
}

int get_line(char s[], int lim)
{
    int i, c;

    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}
