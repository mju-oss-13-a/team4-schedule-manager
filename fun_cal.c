#include "sm_head.h"
/*** if inputed year is leap year, then return 1 ***/
int cfr_leap(int val_year){
	/*** before 1800, all Feb month has 29 days. ***/
	if(val_year<1800){
		if(val_year%4==0){
			return 1;
		}
		else{
			return 0;
		}
	}
	/*** After 1800.. ***/
	else{
		if(val_year%4==0){
			/*** if inputed year is div 4, 100 and not div 400, then the year is not leap year!! ***/
			if((val_year%100==0)&&(val_year%400!=0)){
				return 0;
			}
			/*** other cases, the year is leap year!! ***/
			else{
				return 1;
			}
		}
	}
}
/*** return days of Jan. 1th of inputed year (sun; return 0, mon; return 1, ..., sat; return6)***/
int ret_day_year(int val_year){
	int i, day=6; /*** 0001.01.01's day is Saturday. 'day' is its day.***/
	for(i=1;i<val_year;i++){/*** i = i + 1 per year ***/
		if(i==1752){ /*** 1752.09 has only 17 days, then.. ***/
			day -= 2;
			continue;
		}
		if(cfr_leap(i)==1){ /*** if 'i'year is leap year ... ***/
			day += 2;
		}
		else{
			day++;
		}
	}
	return day%7;
}
/*** return the number of days of inputed month ***/
int ret_date_no(int val_year, int val_month){
	if((val_month==1)||(val_month==3)||(val_month==5)||(val_month==7)||(val_month==8)||(val_month==10)|
		|(val_month==12)){
			return 31;
	} /* if val_month is 1, 3, 5, 7, 8, 10 or 12, then return 31 */
	else if(val_month==2){
		if(cfr_leap(val_year)==1){
			return 29; /* if val_month is Feb and leap month, then return 29 */
		}
		else{
			return 28; /* if val_month is Feb and not leap month, then return 28 */
		}
	}
	else{
		return 30; /* other months, return 30 */
	}
}
/*** return days of Jan. 1th of inputed year and month ***/
int ret_day_mon(int val_year, int val_month){
	int result=0, i;
	for(i=1;i<val_month;i++){ /*** sum days of each month ***/
		result += ret_date_no(val_year, i);
	}
	result += ret_day_year(val_year); /*** sum day of Jan. 1th of inputed year ***/
	return result%7;
}
/*** Print week of inputed year.inputed month ***/
void prn_week(int val_year, int val_month, int line_no){
	int val_days, val_default, i, limit;
	int first_day_of_month;
	int tmp[42];
	val_days = ret_date_no(val_year, val_month); /*** the number of date is saved in val_days ***/
	first_day_of_month = ret_day_mon(val_year, val_month); /*** first day of month is saved in
														   first_day_of_month ***/
	val_default = 1 - first_day_of_month; /*** initial value is saved val_defalut ***/
	for(i=0;i<42;i++){
		tmp[i] = val_default++; /*** tmp[0] = val_default, tmp[1] = val_default + 1, ...***/
	}
	for(i=(7*line_no-7), limit=i+6;i<limit+1;i++){
		prn_date(val_year, val_month, tmp[i]); /*** print date per date ***/
	}
}
/*** Print date ***/
void prn_date(int val_year, int val_month, int val_date){
	int val_max;
	char date[9]={0};
	/*** convert integer values to string values ***************/
	sprintf(date, "%04d%02d%02d", val_year, val_month, val_date);
	/***********************************************************/
	val_max = ret_date_no(val_year, val_month); /*** Max_date is saved in val_max ***/
	if((val_date>=1)&&(val_date<=val_max)){
		if(access(&date[0],00)==0){ /*** if file exsists ***/
			printf("%3d*", val_date);
		}
		else{ /*** if file doesn't exsist ***/
			printf("%3d ", val_date);
		}
	}
	else{ /*** if n is not values in month ***/
		printf(" ");
	}
}
/*** Print calender of inputed year ***/
void prn_cal_year(int val_year){
	int i, j, val_month=1, k=1;
	int a, b, c;
	printf(" %4d₩n", val_year);
	for(i=1;i<5;i++){ /*** (print Calender per 3 months line)*3 ***/
		printf(" %s ", ret_mon_name(k++)); /*** print first month ***/
		printf(" %s ", ret_mon_name(k++)); /*** print second month ***/
		printf(" %s ₩n", ret_mon_name(k++)); /*** print third month ***/
		printf(" Sun Mon Tue Wed Thu Fri Sat ");
		printf(" Sun Mon Tue Wed Thu Fri Sat ");
		printf(" Sun Mon Tue Wed Thu Fri Sat ");
		putchar('₩n');
		for(j=1, a=val_month++, b=val_month++, c=val_month++;j<7;j++){ /*** print calender 1st week to
																	   6th week ***/
			printf(" ");
			prn_week(val_year, a, j);
			printf(" ");
			prn_week(val_year, b, j);
			printf(" ");
			prn_week(val_year, c, j);
			putchar('₩n');
		}
		putchar('₩n');
	}
}
/*** Print calender of inputed month in inputed year ***/
void prn_cal_month(int val_year, int val_month){
	int i;
	printf(" %4d %s ₩n", val_year, ret_mon_name(val_month)); /*** print year and month
															 ***/
	printf(" Sun Mon Tue Wed Thu Fri Sat ₩n");
	for(i=1;i<7;i++){ /*** print calender 1st week to 6th week ***/
		putchar(' ');
		prn_week(val_year, val_month, i);
		putchar('₩n');
	}
	putchar('₩n');
}
/*** Return month name ***/
char *ret_mon_name(int val_month){
	switch(val_month){
	case 1:return "Jan";
	case 2:return "Feb";
	case 3:return "Mar";
	case 4:return "Apr";
	case 5:return "May";
	case 6:return "Jun";
	case 7:return "Jul";
	case 8:return "Aug";
	case 9:return "Sep";
	case 10:return "Oct";
	case 11:return "Nov";
	case 12:return "Sep";
	}
}