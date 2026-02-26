/*
 * Author: Tanmmoy Hasan Raju
 * Date: 2026-02-25
 * Time: 21:58
*/
#include <stdio.h>

// static char *name[] = {"...", ...};  <---------- This represents name is an array
// of pointer to char. So, a pointer to char is eventually a pointer to that string
// it points.

static char *name[] = {
        "Illegal month",
        "January", "February",
        "March", "April", "May",
        "June", "July", "August",
        "September", "October",
        "November", "December"
};

// Here name is an array of strings, or in other words name is an array of pointers
// to char. 


//* Consider the problem of writing a function month_name(n), which returns a pointer
//* to a character string containing the name of the n-th month. This is an ideal app-
//* lication for an internal static array. month_name contains a private array of char-
//* acter strings, and returns a pointer to the proper one when called. This section
//* shows how that array of names is initialized.

//* The syntax is similar to previous initializations:

/* month_name: return name of n-th month */
char *month_name(int n)
{
        static char *name[] = {
                "Illegal month",
                "January", "February",
                "March", "April", "May",
                "June", "July", "August",
                "September", "October",
                "November", "December"
        };
        return (n < 1 || n > 12) ? name[0] : name[n];
}

int main()
{
        printf("%s\n", month_name(1));
        return 0;
}