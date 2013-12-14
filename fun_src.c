#include "sm_head.h"
/*** search date that has a keword ***/
void src(char *str, char *word){
	ELEMENTS_OF_DATE year1=0, mon1=0, date1=0, /* initial values of search range */
					 year2=0, mon2=0, date2=0; /* end values of search range */
	TEMP_INT_VARIABLES i, /* temp variables for loop */
					   cnt = 0;
	VARIABLES_FOR_ARRAY sdate1[10], sdate2[10], /* date string of initial and end of range */
						sdate_tmp[14]; /* temporary date string for scanning values */
	printf("=============================================\n");
	printf("\n Search Result by keyword \"%s\" : \n\n\n", word);
	sscanf(str, "%d %d %d ~ %d %d %d", &year1, &mon1, &date1, &year2, &mon2, &date2);
	/* range values is scaned from str */
	if((year1<=0)||(mon1<=0)||(date1<=0)||(year2<=0)||(mon2<=0)||(date2<=0)){
		printf("\n\nIncorrect range values.. try again..\n\n");
		return;
	}
	sprintf(sdate1, "%04d%02d%02d", year1, mon1, date1); /* print initial values to sdate1 for file handling */
	sprintf(sdate_tmp,"%04d %02d %02d", year1, mon1, date1); /* print initial values to sdate_tmp for scanning values */
	sprintf(sdate2, "%04d%02d%02d", year2, mon2, date2);/* print end values to sdate2*/
	for(i=0;strcmp(sdate1, sdate2)<=0;){ /* during sdate1<=sdate, this loop is excuted.*/
		if(access(sdate1,00)==0){/* if sdate1 file exists */
			cnt += src_body(sdate1, sdate_tmp, word); /* call src_body */
		}
		add_date(sdate1, sdate_tmp); /* add 1 date to sdate1 */
	}
	printf("\n\n % d schedules founded. Thanks.\n\n", cnt);
	printf("=============================================\n");
}
/*** count number of character of file ***/
int cnt_chr(char *file_name){
	int N=1;
	char c;
	FILE *ifp;
	ifp = fopen((char*)file_name, "r");
	while((c=getc(ifp))!=EOF){
		N++;
	}
	return N;
}
/*** searching body that includes keyword ***/
int src_body(char *sdate1, char *sdate_tmp, char *word){
	TEMP_INT_VARIABLES i = 0, cnt = 0;
	VARIABLES_FOR_ARRAY *str_tmp; /* temporary space for saving strings that file has */
	TEMP_CHAR_VARIABLES c;
	FILE *ifp;
	ifp = fopen((char*)sdate1, "r"); /* file open */
str_tmp = (char*)calloc(cnt_chr(sdate1)+1, sizeof(char)); /* location pointer str_tmp */
	while((c=getc(ifp))!=EOF){ /* get char and make string */
		*(str_tmp + (i++)) = c;
	}
	if((strstr(str_tmp, word))!=NULL){ /* If file_tmp include word */
		printf(" \"%s\" is founded in %s.\n", word, sdate1);
		cnt++;
	}

	fclose(ifp); /* close the file */
	free(str_tmp);
	return cnt;
}
/*** add 1 date ***/
void add_date(char *sdate1, char *sdate_tmp){
	int year, date, month;
	sscanf(sdate_tmp, "%d %d %d", &year, &month, &date); /* scan values from sdate_tmp */
	if(date<ret_date_no(year, month)){ /* if date is not end of month.. */
		date++;
	}
	else if(date==ret_date_no(year, month)){ /* if date is end of month.. */
		if(month<12){ /* if month is not end of year.. */
			month++;
			date=1;
		}
		else{ /* if month is end of year.. */
			year++;
			month=1;
			date=1;
		}
	}
	sprintf(sdate1, "%04d%02d%02d", year, month, date); /* print values to sdate1 for file handling */
	sprintf(sdate_tmp, "%04d %02d %02d", year, month, date); /* print values to sdate_tmp for scanning */
}
