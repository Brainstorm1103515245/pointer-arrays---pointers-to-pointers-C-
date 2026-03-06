/*
 * Author: Tanmmoy Hasan Raju
 * Date: 2026-02-26
 * Time: 23:33
*/

// This is the section where your random C program gets elevated into a Software
// level program. Users can directly input or dynamically input arguments to your
// program.

//* In environments that support C, there is a way to pass command-line arguments or
//* parameters to a program when it begins executing. When main is called, it is call-
//* ed with two arguments. The first (conventionally called argc, for argument count)
//* is the number of command-line arguments the program was invoked with; the second
//* (argv, for argument vector) is a pointer to an array of character strings that
//* contain the arguments, one per string. We customarily use multiple levels of
//* pointers to manipulate these character strings.

// How main Receives Arguments
// In hosted C environments, main can be written as:
// int main(int argc, char *argv[])
// or equivalently:
// int main(int argc, char **argv)
// Both mean the same thing.

// What argc Means
// argc = argument count
// It tells you how many command-line arguments were provided.

// Important rule:
// argc is always at least 1.

// Why?
// Because the program name itself is the first argument.

// Example:
// ./program hello world

// Then:
// argc = 3

// Arguments:
// argv[0] → "./program"
// argv[1] → "hello"
// argv[2] → "world"

// What argv Really Is
// This is where pointer magic begins.
// argv is:
// pointer → array of pointers → strings

// Visually:
// argv
//   ↓
// +--------+        +-----+-----+-----+
// | argv[0]| -----> | . | / | p | ... |
// +--------+        +-----+-----+-----+
// | argv[1]| -----> | h | e | l | l | o | \0
// +--------+
// | argv[2]| -----> | w | o | r | l | d | \0
// +--------+
// |  NULL  |

// So:
// argv → pointer to first element of array
// argv[i] → pointer to a string
// argv[i][j] → individual character

// Why “Multiple Levels of Pointers”?
// Because:
// char **argv

// means:
// argv → pointer
// pointing to → pointer
// pointing to → char
// Let’s break types carefully:

// Expression	Type	Meaning
// argv	char **	pointer to pointer to char
// argv[i]	char *	pointer to first char of a string
// argv[i][j]	char	actual character

// That’s why K&R says:
// “We customarily use multiple levels of pointers…”
// Because you’re handling:
// an array
// of pointers
// to strings

//* The simplest illustration is the program echo, which echoes its command-line
//* arguments on a single line, separated by blanks. That is, the command
//*     echo hello, world
//* prints the output
//*     hello, world
// At these stage, we are jumping into the real side applications of the C Progr-
// amming language. We are passing arguments directly into the program while it
// is is runtime. We can definitely call it dynamic input method. Which we can 
// see in operating system line UNIX(linux) which uses command line applications.

//* By convention, argv[0] is the name by which the program was invoked, so argc is
//* at least 1. If argc is 1, there are no command-line arguments after the program
//* name. In the example above, argc is 3, and argv[0], argv[1], and argv[2] are
//* "echo", "hello,", and "world" respectively. The first optional argument is argv[1]
//* and the last is argv[argc-1]; additionally, the standard requires that argv[argc]
//* be a null pointer.

//* Leter after the excerpt, we can see a diagram representing what the argv actually
//* is, we can see argv is a pointer, which points to the poiners which points to the 
//* actual arguments.

// It is called argument vector because:
// It is an ordered list (vector) of the program’s arguments.


#include <stdio.h>

int main_I(int argc, char *argv[])
{
        int i;

        for (i = 1; i < argc; i++) {
                printf("%s", argv[i]);
                if (i < argc - 1)
                        printf(" ");
        }
        printf("\n");
        return 0;
}

/* echo command-line arguments; 1st version */ 
int main_II(int argc, char *argv[])
{
        int i;

        for (i = 1; i < argc; i++)
                printf("%s%s", argv[i], (i < argc - 1) ? " " : "");
        printf("\n");
        return 0;
}

//* Since argv is a pointer to an array of pointers, we can manipulate the pointer
//* rather than index the array. This next variant is based on incrementing argv,
//* which is a pointer to pointer to char, while argc is counted down:

int main_III(int argc, char *argv[])
{
        while (--argc > 0)
                //printf("%s%s", *++argv, (argc > 1) ? " " : "");
                printf((argc > 1) ? "%s " : "%s", *++argv);
        printf("\n");
        return 0;
}

//* Since argv is a pointer to the beginning of the array of argument strings, incrementing
//* it by 1 (++argv) makes it point at the original argv[1] instead of argv[0]. Each successive
//* increment moves it along to the next argument; *argv is then the pointer to that argument.
//* At the same time, argc is decremented; when it becomes zero, there are no arguments left
//* to print.

//* Alternatively, we could write the printf statement as-
//* printf((argc > 1) ? "%s " : "%s", *++argv);
//* This shows that the format argument of printf can be an expression too.
// Meaning the %s%s can be expression too.

//----------------------------------------------------------------------------------------------
#include <string.h>


//* As a second example, let us make some enhancements to the pattern-finding program from Section
//* 4.1. If you recall, we wired the search pattern deep into the program, an obviously unsatisfac-
//* tory arrangement. Following the lead of the UNIX program grep, let us enhance the program so the
//* pattern to be matched is specified by the first argument on the command line.
// They previously wrote a program (in Section 4.1) that searches for a pattern in input text.
// Now they want to improve it.
// “Second example” → This is another demonstration of how command-line arguments can be useful.
// “Enhancements” → The program works, but it’s limited.
// In Section 4.1, the search pattern was hardcoded, something like:
// char pattern[] = "ould";	/* pattern to search for */
// So the program always searched for "ould".
// That is what they mean by:
// “wired the search pattern deep into the program”
// Meaning:
// The pattern is fixed at compile time
// To change it, you must edit source code and recompile.
// “Obviously unsatisfactory” because:
// It’s not flexible.
// Real tools shouldn’t require recompilation for simple changes.
// It violates good software design principles.
// This is K&R subtly teaching you about abstraction and flexibility.
// “Following the lead of the UNIX program grep…”
// This is important.
// They are referencing:
// grep
// grep is the classic Unix tool that searches for patterns in text files.
// Example:
// grep hello file.txt
// The pattern "hello" is passed as a command-line argument.
// K&R is saying:
// Let’s imitate how real Unix tools work.
// This is a philosophy lesson, not just syntax.
// “…let us enhance the program so the pattern to be matched is specified by the first argument
// on the command line.”
// This is the key transformation.
// Instead of:
// char pattern[] = "ould";	/* pattern to search for */
// We will use:
// argv[1]
// Meaning:
// The pattern is no longer hardcoded.
// The user supplies it at runtime.
// The program becomes general-purpose.
// Before:
// Program + fixed pattern → searches input
// After:
// Program + user-provided pattern → searches input
// This changes the program from:
// A specific tool
// to
// A reusable utility
// That’s a major shift in software design maturity. <--------------- Exactly what we need! We are moving toward this gradually, so you the reader have perserverence and be persistant through the journey!

// The Deeper Philosophy K&R Is Teaching
// Programs should not be rigid.
// Programs should accept parameters.
// Real Unix tools are small, flexible, composable.
// Command-line arguments are how Unix achieves flexibility.
// This paragraph is not just about argv.

// It is about:
// Software evolution
// Tool design
// Unix philosophy

#define MAXLINE 1000

int get_line(char line[], int maxlines);

/* find : print lines that match pattern from 1st arg */
int main_IV(int argc, char *argv[])
{
        char line[MAXLINE];
        int found = 0;

        if (argc != 2)
                printf("usage: find pattern\n");
        else {
                while ((get_line(line, MAXLINE)) > 0) {
                        if (strstr(line, argv[1]) != NULL) {
                                printf("%s", line);
                                found++;
                        }
                }
        }
        return found;
}

int get_line(char line[], int maxlines)
{
        int i, c;

        i = 0;
        while (i < maxlines-1 && (c = getchar()) != EOF && c != '\n')
                line[i++] = c;
        if (c == '\n')
                line[i++] = '\n';
        line[i] = '\0';
        return i;
}

//* The standard library function strstr(s,t) returns a pointer to the first occurrence
//* of the string t in the string s, or NULL if there is none. It is declared in <string.h>.

//* The model can now be elaborated to illustrate further pointer constructions. Suppose we
//* want to allow two optional arguments. One says `print all the lines except those that
//* match the pattern;'' the second says precede each printed line by its line number.''

// The Text
// “The model can now be elaborated to illustrate further pointer constructions.”

// Meaning:
// We already used:
// argc
// argv
// argv[1]

// Now K&R wants to show more advanced pointer manipulation — especially walking through argv
// and interpreting options.
// This is about deeper pointer usage, not just simple indexing.

// “Suppose we want to allow two optional arguments.”
// So now the program won’t just accept:
// find pattern
// It may accept options like:
// find -x -n pattern
// Optional arguments = flags that modify behavior.
// This is an invert match option.
// So if pattern is "hello":
// Instead of printing lines containing "hello",
// we print lines that do NOT contain "hello".

// “the second says ‘precede each printed line by its line number.’”
// This is a line numbering option.

// So instead of:
// hello world
// say hello

// You would see:
// 3: hello world
// 7: say hello

//* A common convention for C programs on UNIX systems is that an argument that begins with a
//* minus sign introduces an optional flag or parameter. If we choose -x (for ``except'') to
//* signal the inversion, and -n (``number'') to request line numbering, then the command
//*     find -x -n pattern
//* will print each line that doesn't match the pattern, preceded by its line number.

//* Optional arguments should be permitted in any order, and the rest of the program should be
//* independent of the number of arguments that we present. Furthermore, it is convenient for
//* users if option arguments can be combined, as in
//*      find -nx pattern

//* Here is the program:


#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int get_line(char *line, int max);

/* find: print lines that match pattern from 1st arg */
int main_V(int argc, char *argv[])
{
        char line[MAXLINE];
        long lineno = 0;
        int c, except = 0, number = 0, found = 0;

        while (--argc > 0 && (*++argv)[0] == '-')
                while (c = *++argv[0])
                        switch (c) {
                        case 'x':
                                except = 1;
                                break;
                        case 'n':
                                number = 1;
                                break;
                        default:
                                printf("find: illegal operation %c\n", c);
                                argc = 0;
                                found = -1;
                                break;
                        }
        if (argc != 1)
                printf("Usage: find -x -n pattern\n");
        else
                while (get_line(line, MAXLINE) > 0) {
                        lineno++;
                        if ((strstr(line, *argv) != NULL) != except) {          // except = 0 or 1
                                if (number)
                                        printf("%ld:", lineno);
                                printf("%s", line);
                                found++;
                        }
                }
        return found;
}

//* argc is decremented and argv is incremented before each optional argument. At the end
//* of the loop, if there are no errors, argc tells how many arguments remain unprocessed
//* and argv points to the first of these. Thus argc should be 1 and *argv should point at
//* the pattern. Notice that *++argv is a pointer to an argument string, so (*++argv)[0]
//* is its first character. (An alternate valid form would be **++argv.) Because [] binds
//* tighter than * and ++, the parentheses are necessary; without them the expression would
//* be taken as *++(argv[0]). In fact, that is what we have used in the inner loop, where
//* the task is to walk along a specific argument string. In the inner loop, the expression
//* *++argv[0] increments the pointer argv[0]!

//* It is rare that one uses pointer expressions more complicated than these; in such cases,
//* breaking them into two or three steps will be more intuitive.

//* Exercise 5-10. Write the program expr, which evaluates a reverse Polish expression from
//* the command line, where each operator or operand is a separate argument. For example,
//*     expr 2 3 4 + *
//* evaluates 2 * (3+4).


//! The source file is not completed yet!