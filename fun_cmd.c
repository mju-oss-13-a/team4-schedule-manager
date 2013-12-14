#include "sm_head.h"
/*** Edit schedule ***/
void CMD_edit(char *date){
	TEMP_CHAR_VARIABLES c, tmp;
	FILE *ofp;
	if(access(&date[0],00)==0){ /*** If there is a same file.. ***/
		printf("There is already saved schedule!!\n");
		printf("Are you sure change the schedule?? [Y/N]");
		scanf("%c", &tmp);
		if((tmp=='Y')||(tmp=='y')){
		}
		else{
			printf("\n\nProceess is aborted.\n\n");
			fflush(stdin);
			return; /*** exit functions ***/
		}
	}
	printf("\n\n[Edit : %s]\n", date);
	ofp = fopen((char*)date, "w"); /*** open file for write ***/
	while((c=getchar())!=EOF){ /*** until EOF, get character from keboaard and put it in file ***/
			putc(c, ofp);
			
	}
	printf("\n\nSchdule is edited successfully!!\n\n");
	fclose(ofp);
}
/*** Delete schedule ***/
void CMD_del(char *date){
	TEMP_CHAR_VARIABLES c;
	printf("[Delete : %s]\n", date);
	if(access(&date[0],00)!=0){ /*** If there is not a file, print error massage! ***/
		printf("There is not exist schedule!!\n");
		return;
	}
	printf("\n%s schedule will be removed! Are you OK? [Y/N]", date); /*** confirm that really ***/

	scanf("%c", &c);
	if((c=='Y')||(c=='y')){
		remove(date);
		fflush(stdin);
		printf("\n\n%s Schedule is deleted!\n", date);
	}
	else{
		printf("\n\nProcess is aborted!\n");
		fflush(stdin);
		return ;
	}
}
/*** Command that view schdule ***/
void CMD_view(char *date1, char *date2){
	ELEMENTS_OF_DATE val1y, val1m, val1d, /* Initial date element */
					 val2y, val2m, val2d, /* End date element */
					 val1s, val2s; /* valNs = valNy + valNm + valNd (N=1, 2, ...) */
	TEMP_INT_VARIABLES sum, mode;
	TEMP_CHAR_VARIABLES c;
	VARIABLES_FOR_ARRAY date[8]; /* file name of the date */
	FILE *ifp;
	sscanf(date1, "%04d %02d %02d", &val1y, &val1m, &val1d); /* scanf values ..*/
	sscanf(date2, "%04d %02d %02d", &val2y, &val2m, &val2d); /* scanf values ..*/
	sprintf(date, "%04d%02d%02d", val1y, val1m, val1d); /* print dates to date for file handling */
	val1s = val1y*10000 + val1m*100 + val1d; /* make date string to integer */
	val2s = val2y*10000 + val2m*100 + val2d; /* make date string to integer */
	if(val1s>val2s){ /*if date2 is before date1 */
		sum = cnt_date(val2y, val2m, val2d, val1y, val1m, val1d); /* call cnt_date() */
		mode = 0;
	}
	else if(val1s==val2s){ /* if date1 equivalences to date2 */
		mode = 1;
	}
	else if(val1s<val2s){ /*if date1 is before date2 */
		sum = cnt_date(val1y, val1m, val1d, val2y, val2m, val2d); /* call cnt_date() */
		mode = 2;
	}
	if(access(&date[0],00)!=0){ /*** If there is not a file, print error massage ***/
		return;
	}
{
	ifp = fopen(&date[0], "r"); /* open file */
	putchar('\n');
	switch(mode){
		case 0:
			printf("[Schedule : %s, %d days left.]\n", date, sum);
			break;
		case 1:
			printf("[Schedule : %s, Today schedule.]\n", date);
			break;
		case 2:
			printf("[scehdule : %s, %d days passed.]\n", date, sum);
			break;
	}
	while((c=getc(ifp))!=EOF){ /*** Get character and put it on screen ***/
		putchar(c);
	}
	putchar('\n');
	putchar('\n');
	fclose(ifp);
}
}
/*** Search Schedule ***/
void CMD_src(void){
	VARIABLES_FOR_ARRAY str[50]={0}, /* range for searching */
						word[50]={0}; /* keyword */
	TEMP_CHAR_VARIABLES c;
	printf("\n\nInput Keyword : ");
	my_gets(word,sizeof(word)); /* input keyword */
	printf("\n\nInput range for searching [ex:2003 5 3 ~ 2005 7 12] :");
	my_gets(str,sizeof(str)); /* input range */
	src(&str[0], &word[0]); /* call src() */
}
/*** Print help page ***/
void CMD_help(void){
	printf("\n\n\n+-------------------------------------------------------+\n");
	printf("|            |\n");
	printf("| Schedule Manager v1.0 |\n");
	printf("| |\n");
	printf("| - developer : Kim Gook-hyun. |\n");
	printf("| - created : 2005.05.04 - 2005.05.13 |\n");
	printf("| - e-mail : kimegoo@hanmail.net |\n");
	printf("| |\n");
	printf("| *Command* |\n");
	printf("| |\n");
	printf("| - YYYY MM [enter] : show calender of the month |\n");
	printf("| - YYYY MM DD [enter] : view schedule of that day |\n");
	printf("| - v date : view schedule of that day |\n");
	printf("| - h : print help page |\n");
	printf("| - e : edit or creat a schedule |\n");
	printf("| ex)command : e 2005 04 01 [ENTER] |\n");
	printf("| - d : delete schedule |\n");
	printf("| ex)command : d 2005 04 01 [ENTER] |\n");
	printf("| - s : seach schedule |\n");
	printf("| - end : exit the program |\n");
	printf("| |\n");
	printf("+-------------------------------------------------------+\n\n\n");
}
