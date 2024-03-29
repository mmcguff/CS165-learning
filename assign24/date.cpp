#include "date.h"

/**********************************************************************
 * INITIALIZE.  Initialize the year to 1/1/2000
 *  OUTPUT: date:  the adjusted date
 ***********************************************************************/
Date :: Date(int year) : day(1), month(1), year(year)
{
   assertDate();
}

/**********************************************************************
 * INITIALIZE.  Initialize the year to 1/1/2000
 *  OUTPUT: date:  the adjusted date
 ***********************************************************************/
Date :: Date(int year, int month, int day) : day(day), month(month), year(year)
{
   assertDate();
}

/**********************************************************************
 * INITIALIZE.  Initialize the year to 1/1/2000
 *  OUTPUT: date:  the adjusted date
 ***********************************************************************/
Date :: Date() : day(1), month(1), year(2000)
{
   assertDate();
}

/********************************************************
 * UNINITIALIZE.  Free up the memory we allocated
 *  INPUT:  date:  What we will be freeing up
 *  OUTPUT: date:  No longer ready for use
 ********************************************************/
Date :: ~Date()
{
   assertDate();
}


/*********************************************************
 * SET DATE.  Set all 3 fields of the date type and doing error checking
 *   INPUT  day    Day between 1 and 31 (or 28, depending)
 *          month  Month between 1 and 12
 *          year   After 1753, before something crazy
 *   OUTPUT date   The newly formed type
 *          return Success?
 **********************************************************/
bool Date :: setDate(int year, int month, int day)
{
   // validation
   if (year < 1753 || year > 2500)
      return false;
   if (month < 1 || month > 12)
      return false;
   if (day < 1 || day > daysMonth(month, year))
      return false;

   // assignment
   this->year = year;
   this->month = month;
   this->day = day;

   assertDate();

   return true;
}

/*****************************************************
 * DAYS MONTH.  How many days are there in the current month?
 *   INPUT  month    the month we are inquiring about
 *          year     we only care about this when month == 2
 *   OUTPUT return   return the number
 *****************************************************/
int Date :: daysMonth(int month, int year)
{
   if (month > 12 || month < 1)
   {
      assert(false);
      return 0;
   }

   const int DAYS[13] =
       /* JAN FEB MAR APR MAY JUN JUL AUG SEP OCT NOV DEC */
      { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   // special case the one leap month
   if (month == 2 && isLeapYear(year))
      return 29;

   assert(month > 0 && month < 13);
   return DAYS[month];
}

/***********************************************
 * IS LEAP YEAR.  Is the passed year a leap year?
 *   INPUT   year    The current year
 *   OUTPUT  return  True if we are in a leap year
 **********************************************/
bool Date :: isLeapYear(int year)
{
   // no leap years before 1753
   assert(year >= 1753);

   // what, are you Buck Rogers?
   assert(year < 2500);

   // Not a leap year if not evenly divisible by 4
   // This will eliminate 75% of all years
   if (year % 4 != 0)
      return false; // 2001, 2002, 2003, 2005, etc.
   assert(year % 4 == 0);

   // Is a leap year if not divisible by 100
   // This will eliminate 96% of the rest
   if (year % 100 != 0)
      return true; // 1996, 2004, 2008, 2012, etc.
   // We better be 1800, 1900, 2000, 2100 at this point
   assert(year % 100 == 0);

   // Is a leap year if on the quad century
   if (year % 400 == 0)
      return true; // 1600, 2000, 2400, etc.
   // It better be something like 1800, 1900, 2100, etc.
   assert(year % 400 != 0);

   // the balance better be 1900, 1800, etc.
   assert(year == 1800 || year == 1900 || year == 2100 || year == 2200);
   return false;
}

/**********************************************
 * DISPLAY LONG.  Display the current date: 1st of October, 2009
 *  INPUT date   the current date
 *********************************************/
void Date :: displayLong()
{
   assertDate();

   // day
   cout << day;
   switch (day)
   {
      case 1:
      case 21:
      case 31:
         cout << "st";
         break;
      case 2:
      case 22:
         cout << "nd";
         break;
      case 3:
      case 23:
         cout << "rd";
         break;
      default:
         cout << "th";
   }

   // month
   const char MONTHS[12][10] =
      { "January", "February", "March",     "April",   "May",      "June",
        "July",    "August",   "September", "October", "November", "December"};

   cout << " of " << MONTHS[month - 1] << ", ";

   // year
   cout << year;
}


/************************************************
 * ASSERT DATE.  Validate date
 *   INPUT date: the date to be validated
 ***********************************************/
void Date :: assertDate()
{
   string file = __FILE__;
   int line = __LINE__;
   // validate the year.  Keep it real
   if (year < 1753 || year > 2500)
   {
      cerr << "Assert: " << file << ": " << line
           << ": date.year=" << year << " outside valid range\n";
      exit(1);
   }

   // valide the month
   if (month < 1 || month > 12)
   {
      cerr << "Assert: " << file << ": " << line
           << ": date.month=" << month << " outside valid range\n";
      exit(1);
   }

   // finally the day.
   if (day < 1
       || day > daysMonth(month, year))
   {
      cerr << "Assert: " << file << ": " << line
           << ": date.day=" << day << " outside valid range\n";
      exit(1);
   }
}
