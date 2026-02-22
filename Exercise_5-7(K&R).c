/*
 * Author: Tanmmoy Hasan Raju
 * Date: 2026-02-21
 * Time: 14:53
*/

//* So, after reading the lexicographical string sorting program in the K&R C programming Language
//* I have learned a bunch of stuffs, and at the end the authors gave an example to implement what
//* i have learned through the program. 

//* Exercise 5-7. Rewrite readlines to store lines in an array supplied by main, rather than calling
//* alloc to maintain storage. How much faster is the program?

//* So, before readring the code or understanding the code, my suggestion to you (The READER), go
//* first try to understand the main program written in the book deeply, you must be able to keep
//* track of the programs(how they work integratedly) and how each of the function works from scra-
//* tch. If you do that you are good to go...

//* Now i am going to 


// Sorting strings lexicographically in The C Programming Language
#include <stdio.h>
#include <string.h>

#define MAXLINES    2000000

char *lineptr[MAXLINES];

int readlines_I(char *lineptr[], int nlines);
int readlines_II(char *lineptr[], char [], int nlines, char *);
void writelines(char *lineptr[], int nlines);
void qsort(char *v[], int left, int right);

#define MAINBUFSIZE     1000000

int main()
{
    int nlines;
    static char MAINBUF[MAINBUFSIZE];
    static char *p = MAINBUF;

    if ((nlines = readlines_II(lineptr, MAINBUF, MAXLINES, p)) > 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Error: input too big to sort!\n\a");
        return 0;
    }
}

#define MAXLEN      2000000
int get_line(char arr[], int nlines);
char *alloc(int);

//int readlines_I(char *lineptr[], int maxlines)
//{
//    int len, nlines;
//    char *p, line[MAXLEN];
//
//    nlines = 0;
//    while ((len = get_line(line, MAXLEN)) > 0) {
//        if (nlines >= MAXLINES || (p = alloc(len)) == NULL)
//            return -1;
//        else {
//            line[len-1] = '\0';
//            strcpy(p, line);
//            lineptr[nlines++] = p;
//        }
//    }
//    return nlines;
//}

int readlines_II(char *lineptr[], char BUFARRAY[], int maxlines, char *p)          // <------------------------------------
{
    int len, nlines;
    char line[MAXLEN];

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= MAXLINES)
                return -1;
        else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int get_line(char arr[], int len)
{
    int c, i;

    i = 0;
    while (i < len-1 && (c = getchar()) != EOF && c != '\n' && len-- > 0)
        arr[i++] = c;
    if (c == '\n')
        arr[i++] = '\n';
    arr[i] = '\0';
    return i;
}



#define ALLOCSIZE       2000000         // ~Approximately 2MB
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

#define BAR_WIDTH       50

void print_bar(void)
{
    int used = allocp - allocbuf;
    int total = ALLOCSIZE;

    int width = (used*BAR_WIDTH)/total;

    for (int i = 0; i < BAR_WIDTH; i++) {
        if (i < width)
            printf("#");
        else
            printf(".");
    }
    printf("\n");
}

char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        //print_bar();
        return allocp - n;
    } else
        return 0;
}

void swap(char *v[], int, int);
void qsort(char *v[], int left, int right)
{
    int i, last;

    if (left >= right)
        return;
    swap(v, left, (left+right)/2);
    last = left;
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

/** Exercise 5-7. Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to
maintain storage. How much faster is the program? **/

