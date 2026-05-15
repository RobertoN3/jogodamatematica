#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// leap: returns true if y is a leap year.  Returns false otherwise 
int leap(int y);

// lastday: returns the last day of the month
int last_day(int d, int m, int y);

int main(int argc, char *argv[])
{
    int d = atoi(argv[1]);
    int m = atoi(argv[2]);
    int y = atoi(argv[3]);

    int last = last_day(d, m, y); // last day of month

    if (d < last) {
        d++;
        printf("%d %d %d\n", d, m, y);
        return 0;
    }
    if (m < 12) {
        d = 1;
        m++;
        printf("%d %d %d\n", d, m, y);
        return 0;
    }
    d = m = 1;
    y++;
    printf("%d %d %d\n", d, m, y);    
    return 0;
}

// leap: returns true if y is a leap year.  Returns false otherwise 
int leap(int y) {
    return ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
}

// lastday: returns the last day of the month
int last_day(int d, int m, int y) {
    if (m == 1 || m == 3 || m == 5 || m == 7
        || m == 8 || m == 10 || m == 12)
        return 31;
    if (m == 4 || m == 6 || m == 9 || m == 11)
        return 30;
    if (m == 2 && leap(y))
        return 29;
    if (m == 2 && !leap(y))
        return 28;
    return -1; // shouldn't happen
}