#include "sm_head.h"
/*** detemine 'c' is command.. (c is command return 1, else return 0) ***/
int iscmd(char c){
	if((c=='e')||(c=='v')||(c=='d')||(c=='h')||(c=='s'))
		return 1;
	else
		return 0;
}
/*** Count dates from intial year to last year ***/
int cnt_date(int ini_year, int ini_month, int ini_date, int end_year, int end_month, int end_date){
	int sum = 0, i;
	if(ini_year!=end_year){ /* if initial year is not same end_year */
		for(i=ini_year+1;i<end_year;i++){ /* add date of the year that inside range of initial and end */
			if((cfr_leap(i))==1){ /* if i is leap year.. */
				sum += 366;
			}
			else{
				sum += 365;
			}
		}
		for(i=ini_month+1;i<13;i++){ /* add date of the month that inside range from initial month to end
									 month of the initial year*/
			sum += ret_date_no(ini_year, i);
		}
		for(i=1;i<end_month;i++){ /* add date of the month that inside range from end month to end
								  month of the end year*/
			sum += ret_date_no(end_year, i);
		}
		sum += ret_date_no(ini_year, ini_month) - ini_date; /* add dates */
		sum += end_date; /* add dates */
	}
	else if(ini_year==end_year){ /* if initial year equivalences to end year */
		if(ini_month!=end_month){ /* if initial month does not equivalences to end month */
			for(i=ini_month+1;i<end_month;i++){ /* add date of the month from initial month to end month
												*/
				sum += ret_date_no(ini_year, i);
			}
			sum += ret_date_no(ini_year, ini_month) - ini_date; /* add dates */
			sum += end_date; /* add dates */
		}
		else{
			sum += end_date - ini_date;
		}
	}
	return sum;
}