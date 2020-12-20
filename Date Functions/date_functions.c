/* date_functions.c
   CSC 111 - Fall 2020 - Assignment 3

   B. Bird - 08/08/2020
   Emila Suska – 2020-10-11
   date_functions.c implements many date-related utility functions
*/

#include <stdio.h>

/* is_leap_year(year)
   Given a year, determine whether that year is a leap year.
   Parameters: year (integer)
   Return value (integer):
     - If the year is a leap year, return 1
     - Otherwise, return 0
  
   For this function _only_, you may assume that the year number
   will always be valid (that is, greater than or equal to 1).
*/
int is_leap_year(int year){
    if (year % 4 != 0) {
        return 0;
    }
    if (year % 100 != 0) {
        return 1;
    }
    if (year % 400 != 0) {
        return 0;
    }
    return 1;
}


/* days_in_year(year)
   Given a year, return the number of days in that year.
   A leap year has 366 days. All other years have 365 days.

   Parameters: year (integer)
   Return value (integer):
     - If year is valid (greater than or equal to 1),
       return the number of days in that year.
     - If year is invalid (negative or zero), return -1.
*/
int days_in_year(int year){
    if (is_leap_year(year)) {
        return 366;
    }
    return 365;
}

/* days_in_month(year, month_number)
   Given a year and a numerical representation of the month (where 1 is January
   and 12 is December), return the number of days in that month.
   
   Note that the number of days in February (month 2) will vary depending on
   whether the year is a leap year.

   Parameters: year (integer), month_number (integer)
   Return value (integer):
     - If the month number is valid (between 1 and 12, inclusive),
       the return value will be the number of days in the provided
       month during the provided year.
     - If the month number is invalid (negative, zero, greater than 12),
       or the year number is invalid (negative or zero),
       the return value will be -1.
*/
int days_in_month(int year, int month_number){
    if (year < 1 || month_number < 1 || month_number > 12) {
        return -1;
    }
    if (month_number == 2) {
        if (is_leap_year(year)) {
            return 29;
        } else {
            return 28;
        }
    }
    if (month_number == 1
        || month_number == 3
        || month_number == 5
        || month_number == 7
        || month_number == 8
        || month_number == 10
        || month_number == 12)
    {
        return 31;
    } else {
        return 30;
    }
}

/* date_valid(year, month_number, day)
   Determine if a particular year/month/day combination is a valid date.
   For example, the dates 2020-01-31, 2020-02-29 and 2020-09-15 are valid,
   but the dates 2020-01-32, 2019-02-29 and 2020-15-09 are not.

   Specifically, a date is valid if
    - The year number is greater than or equal to 1
    - The month number is between 1 and 12 (inclusive)
    - The day number is between 1 and the number of days in the provided
      month during the provided year (note that the number of days in each
      month may vary depending on whether the year is a leap year).

   Parameters: year (integer), month_number (integer), day (integer)
   Return value (integer):
     - If the date is valid, return 1
     - Otherwise, return 0
*/
int date_valid(int year, int month_number, int day){
    if (year < 1) {
        return 0;
    }
    if (month_number < 1 || month_number > 12) {
        return 0;
    }
    if (day < 1 || day > days_in_month(year, month_number)) {
        return 0;
    }
    return 1;
}

/* day_index(year, month_number, day)
   Given a date, return the day index of that date within its year.
   The day index is the number of days between the beginning of the year
   and the date. For example, the day index of 2020-01-01 is 1 and the day
   index of 2020-12-31 is 366 (since 2020 is a leap year).

   Parameters: year (integer), month_number (integer), day (integer)
   Return value (integer):
     - If the date is valid, return the day index of the date
     - Otherwise, return -1
*/
int day_index(int year, int month_number, int day){
    if (!date_valid(year, month_number, day)) {
        return -1;
    }
    int year_day = 0;
    for (int i = 1; i < month_number; ++i) {
        year_day += days_in_month(year, i);
    }
    year_day += day;
    return year_day;
}

/* chronological_order(year1, month1, day1, year2, month2, day2)
   Given two dates year1/month1/day1 and year2/month2/day2, determine which
   date is chronologically earlier (or whether the two dates are equal).

   Parameters (all integers): year1, month1, day1, year2, month2, day2
   Return value (integer):
     - If either (or both) of the provided dates is invalid, return -1.
     - If the two dates are both valid and year1/month1/day1 is chronologically
       earlier than year2/month2/day2, return 1.
     - If the two dates are both valid and year1/month1/day1 is chronologically
       later than year2/month2/day2, return 2.
     - If the two dates are both valid and exactly equal, return 0.
*/
int chronological_order(int year1, int month1, int day1, int year2, int month2, int day2){
    if (!date_valid(year1, month1, day1) || !date_valid(year2, month2, day2)) {
        return -1;
    }
    if (year1 < year2) {
        return 1;
    }
    if (year1 > year2) {
        return 2;
    }
    if (month1 < month2) {
        return 1;
    }
    if (month1 > month2) {
        return 2;
    }
    if (day1 < day2) {
        return 1;
    }
    if (day1 > day2) {
        return 2;
    }
    return 0; // same date
}
   

/* days_in_range(start_year, start_month, start_day, end_year, end_month, end_day)
   Given two dates (year, month, day), determine the total number of days in the range
   defined by those two dates, including the dates themselves.
   For example, the number of days between 2020-01-05 and 2020-01-10
   is six (2020-01-05,2020-01-06,2020-01-07,2020-01-08,2020-01-09,2020-01-10).

   Parameters (all integers): start_year, start_month, start_day, end_year, end_month, end_day
   Return value (integer):
     - If either or both of the start date or end date is not a valid date
       (as determined by the date_valid function above), return -1.
     - If the start date is chronologically later than the end date, return -1.
     - If the start date and end date are both valid dates, and the start date is chronologically
       earlier than or equal to the end date, return the number of days in the range.
*/
int days_in_range(int start_year, int start_month, int start_day, int end_year, int end_month, int end_day){
    int order = chronological_order(start_year, start_month, start_day, end_year, end_month, end_day);
    if (order == 0) {
        return 1;
    }
    if (order != 1) {
        return -1;
    }
    if (start_year == end_year) {
        return day_index(end_year, end_month, end_day) - day_index(start_year, start_month, start_day) + 1;
    }
    int start_year_days = days_in_year(start_year) - day_index(start_year, start_month, start_day);
    int end_year_days = day_index(end_year, end_month, end_day);
    int days_between_years = 0;
    for (int i = start_year + 1; i < end_year; ++i) {
        days_between_years += days_in_year(i);
    }
    return start_year_days + end_year_days + days_between_years + 1;
}

int main(){

    /* The code in main() will not be marked (we will replace your main() with
       our own code for testing). The code below does some basic testing of the
       functions above, but we will use different test cases for marking,
       so you should add extra tests to verify your code.

       Remember to test unusual or "edge" cases as well as normal inputs.
       For example, make sure to test the behavior of each function
       on invalid dates (not just valid ones).
     */

    int result;
    /* Test is_leap_year */
    result = is_leap_year(1); //Should be 0
    printf("is_leap_year(1): %d\n", result );

    result = is_leap_year(2004); //Should be 1
    printf("is_leap_year(2004): %d\n", result );

    result = is_leap_year(1970); //Should be 0
    printf("is_leap_year(1970): %d\n", result );

    result = is_leap_year(1972); //Should be 1
    printf("is_leap_year(1972): %d\n", result );

    result = is_leap_year(1996); //Should be 1
    printf("is_leap_year(1996): %d\n", result );

    result = is_leap_year(2012); //Should be 1
    printf("is_leap_year(2012): %d\n", result );


    /* Test days_in_year */

    result = days_in_year(2020); //Should be 366
    printf("days_in_year(2020): %d\n", result );

    result = days_in_year(2019); //Should be 365
    printf("days_in_year(2019): %d\n", result );

    result = days_in_year(1600); //Should be 366
    printf("days_in_year(1600): %d\n", result );

    result = days_in_year(1700); //Should be 365
    printf("days_in_year(1700): %d\n", result );

    result = days_in_year(1870); //Should be 365
    printf("days_in_year(1870): %d\n", result );


    /* Test days_in_month */

    result = days_in_month(2020, 1); //Should be 31
    printf("days_in_month(2020, 1): %d\n", result );

    result = days_in_month(2020, 2); //Should be 29
    printf("days_in_month(2020, 2): %d\n", result );

    result = days_in_month(2020, 4); //Should be 30
    printf("days_in_month(2020, 4): %d\n", result );

    result = days_in_month(1999, 3); //Should be 31
    printf("days_in_month(1999, 3): %d\n", result );

    result = days_in_month(2006, 2); //Should be 28
    printf("days_in_month(2006, 2): %d\n", result );
    
    result = days_in_month(2006, 9); //Should be 30
    printf("days_in_month(2006, 9): %d\n", result );

    result = days_in_month(2006, 0); //Should be -1
    printf("days_in_month(2006, 0): %d\n", result );
    
    result = days_in_month(2006, 19); //Should be -1
    printf("days_in_month(2006, 19): %d\n", result );
    
    
    /* Test date_valid */

    result = date_valid(2020, 1, 11); //Should be 1
    printf("date_valid(2020, 1, 11): %d\n", result );

    result = date_valid(2020, 2, 29); //Should be 1
    printf("date_valid(2020, 2, 29): %d\n", result );

    result = date_valid(2020, 1, 87); //Should be 0
    printf("date_valid(2020, 1, 87): %d\n", result );

    result = date_valid(2020, 6, 31); //Should be 0
    printf("date_valid(2020, 6, 31): %d\n", result );
    
    result = date_valid(2020, 6, 9); //Should be 1
    printf("date_valid(2020, 6, 9): %d\n", result );

    result = date_valid(-1, 6, 9); //Should be 0
    printf("date_valid(-1, 6, 9): %d\n", result );

    result = date_valid(2700, 6, 9); //Should be 1
    printf("date_valid(2700, 6, 9): %d\n", result );

    result = date_valid(2020, 92, 9); //Should be 0
    printf("date_valid(2020, 92, 9): %d\n", result );

    result = date_valid(0, 6, 6); //Should be 0
    printf("date_valid(0, 6, 6): %d\n", result );

    
    /* Test day_index */

    result = day_index(2020, 6, 10); //Should be 162
    printf("day_index(2020, 6, 10): %d\n", result );

    result = day_index(2020, 10, 6); //Should be 280
    printf("day_index(2020, 10, 6): %d\n", result );

    result = day_index(2019, 6, 10); //Should be 161
    printf("day_index(2019, 6, 10): %d\n", result );

    result = day_index(2019, 1, 1); //Should be 1
    printf("day_index(2019, 1, 1): %d\n", result );

    result = day_index(2019, 1, 32); //Should be -1
    printf("day_index(2019, 1, 32): %d\n", result );
    
    result = day_index(2019, 1, 31); //Should be 31
    printf("day_index(2019, 1, 31): %d\n", result );
    
    result = day_index(2019, 19, 3); //Should be -1
    printf("day_index(2019, 19, 3): %d\n", result );


    /* Test chronological_order */

    result = chronological_order(2019, 10, 6, 2020, 6, 10); //Should be 1
    printf("chronological_order(2019, 10, 6, 2020, 6, 10): %d\n", result );

    result = chronological_order(2019, 10, 6, 2019, 6, 10); //Should be 2
    printf("chronological_order(2019, 10, 6, 2019, 6, 10): %d\n", result );

    result = chronological_order(2019, 6, 10, 2019, 6, 10); //Should be 0
    printf("chronological_order(2019, 6, 10, 2019, 6, 10): %d\n", result );

    result = chronological_order(2019, 6, 10, 2019, 6, 31); //Should be -1
    printf("chronological_order(2019, 6, 10, 2019, 6, 31): %d\n", result );

    result = chronological_order(2000, 6, 10, 2019, 6, 30); //Should be 1
    printf("chronological_order(2000, 6, 10, 2019, 6, 30): %d\n", result );
    
    result = chronological_order(2000, 6, 10, 1919, 6, 1); //Should be 2
    printf("chronological_order(2000, 6, 10, 2019, 6, 1): %d\n", result );

    result = chronological_order(2000, 6, 10, 1919, 63, 1); //Should be -1
    printf("chronological_order(2000, 6, 10, 2019, 63, 1): %d\n", result );


    /* Test days_in_range */

    result = days_in_range(2019, 10, 6, 2020, 6, 10); //Should be 249
    printf("days_in_range(2019, 10, 6, 2020, 6, 10): %d\n", result );

    result = days_in_range(2019, 12, 20, 2020, 1, 11); //Should be 23
    printf("days_in_range(2019, 12, 20, 2020, 1, 11): %d\n", result );

    result = days_in_range(2019, 12, 20, 2019, 1, 11); //Should be -1
    printf("days_in_range(2019, 12, 20, 2020, 1, 11): %d\n", result );
    
    result = days_in_range(1970, 8, 13, 1971, 8, 13); //Should be 366
    printf("days_in_range(1970, 8, 13, 1971, 8, 13: %d\n", result );
    
    result = days_in_range(1970, 8, 130, 1971, 8, 130); //Should be -1
    printf("days_in_range(1970, 8, 130, 1971, 8, 130: %d\n", result );

    result = days_in_range(2020, 10, 11, 2020, 10, 12); //Should be 2
    printf("days_in_range(2020, 10, 11, 2020, 10, 12: %d\n", result );

    result = days_in_range(2020, 10, 12, 2020, 10, 11); //Should be -1
    printf("days_in_range(2020, 10, 12, 2020, 10, 11: %d\n", result );
    
    result = days_in_range(2020, 10, 11, 2020, 10, 14); //Should be 4
    printf("days_in_range(2020, 10, 11, 2020, 10, 14: %d\n", result );
    
    result = days_in_range(2020, 10, 11, 2020, 10, 11); //Should be 1
    printf("days_in_range(2020, 10, 11, 2020, 10, 11: %d\n", result );
    
    result = days_in_range(2020, 10, 30, 2020, 10, 30); //Should be 1
    printf("days_in_range(2020, 10, 30, 2020, 10, 30: %d\n", result );


    return 0;
}
