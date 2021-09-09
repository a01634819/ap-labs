/* Alma Anguiano A01634819*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Initialization
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static char *name[] = {
       "Illegal month",
       "January", "February", "March",
       "April", "May", "June",
       "July", "August", "September",
       "October", "November", "December"
};

int day_of_year(int year,int month,int day);

// month_day function's prototype
void month_day(int year, int yearday, int *pmonth, int *pday){
    int i,leap;

    leap = year % 4 == 0 && year%100 != 0 || year%400 == 0;

    if((yearday < 1) || (leap == 0 && yearday > 365) || (leap == 1 && yearday > 366) ){
        printf("Error\n");
        exit(0); 
    }

    for (int i = 1; i < 12; i++){
        *pmonth = i;
        if (*pday <= daytab[leap][i]){
            return; 
        }
        *pday -= daytab[leap][i];
    }
}

int main(int argc, char **argv) {
    if(argc > 3){
        printf("Error \n");
        return 0;
    }
    
    int x=0;
    int y = atoi(argv[1]);
    int d = atoi(argv[2]);
    
    month_day(y, d, &x, &d);
    printf("%s %02d, %d\n",name[x], d, y);

}
