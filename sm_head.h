/*** Header Files *****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <io.h>
//#include <unistd.h>
/*** Type definitions **************************************************/
typedef int ELEMENTS_OF_DATE;
typedef int TEMP_INT_VARIABLES;
typedef char TEMP_CHAR_VARIABLES;
typedef char VARIABLES_FOR_ARRAY;
/*** Prototypes functions **********************************************/
int cfr_leap(int); // Check input is leap year.
int ret_day_year(int); // Return day of Jan. 1th.
int ret_date_no(int, int); // Return number of date of month.
int ret_day_mon(int,int); // Return day of month. 1th.
int iscmd(char c); // Check c is command.
int src_body(char*,char*,char*); // Loop body for search.
int cnt_chr(char *file_name); // Count character of file.
int cnt_date(int,int,int,int,int,int); // Count number of date.
void prn_week(int, int, int); // Print dates per week.
void prn_date(int, int, int); // Print date.
void prn_cal_year(int); // Print month of the year.
void prn_cal_month(int, int); // Print month of the month.
void add_date(char*,char*); // Add 1 date.
void CMD_help(void); // Print Help Page.
void CMD_edit(char*); // Edit or Create schedule.
void CMD_del(char*); // Delete schedule.
void CMD_src(void); // Seach the schedule.
void CMD_view(char*, char*); // View schedule.
void src(char*, char*); // Search schedule fucntion.
char *ret_mon_name(int); // Return name of month.
char *my_gets(char *s, size_t size);
/***********************************************************************/
