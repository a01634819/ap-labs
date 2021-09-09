/* Alma Anguiano A01634819*/

#include <stdio.h>

//Initialization
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year,int month,int day);
void month_day(int year,int yearday);

/* Get year day from a given year,month and day combination */
int day_of_year(int year, int month, int day){
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 ¦¦ year%400 == 0;

    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day function's prototype
void month_day(int year, int yearday, int *pmonth, int *pday){

}*/

void month_day(int year,int yearday){
    int i,leap;

    leap = year % 4 == 0 && year%100 != 0 || year%400 == 0;

    for(i=1;yearday > daytab[leap][i];i++)
        yearday -= daytab[leap][i];

    
}

/* month_name:  return name of n-th month */
char *month_name(int n) {

   static char *name[] = {
       "Illegal month",
       "January", "February", "March",
       "April", "May", "June",
       "July", "August", "September",
       "October", "November", "December"
   };
   return (n < 1 ¦¦ n > 12) ? name[0] : name[n];
}


int main(void) {

}
