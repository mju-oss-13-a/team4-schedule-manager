#include "sm_head.h"
int main(void){
	CMD_help(); /* Print help page on screen */
	while(1){
		ELEMENTS_OF_DATE val_year = 0, val_month = 0, val_date = 0; /* variables of inputed
																	   date */
		TEMP_CHAR_VARIABLES cmd; /* variable for saving inputed command */
		VARIABLES_FOR_ARRAY cmd_str[13]={0}, /* variable for command string and put them
												NULL values */
							today_above_cmd[16], /* today string on the [command] */
							tod_for_file[9], /* today string for file handling */
							tod_for_scan[14], /* today string for scan values */
							date_for_file[8]={0}, /* date string for file handling */
							date_for_scan[12]; /* date string for scan values */
		TEMP_INT_VARIABLES i, /* temp for loop */
						   chk;
		time_t now = time(NULL);
		strftime(today_above_cmd, 16, "%Y.%m.%d(%a)", localtime(&now)); /* write today date */
		strftime(tod_for_file, 9, "%Y%m%d", localtime(&now)); /* print today date in file handling form */
		if((access(tod_for_file, 00)==0)&&(chk!=1)){ /* If there is a schedule of today, print message! */
			printf("\nThere is a schedule of today!! Please Check!!\n\n");
			chk=1;
		}


		printf("\n%s\n", today_above_cmd); /* print today */
		printf("[Command] "); /* print command prompt */

		my_gets(cmd_str,sizeof(cmd_str)); /* get command string */

		if(iscmd(cmd_str[0])){ /* if cmd_str[0] is command.. */
			if((cmd_str[0]=='e')&&(cmd_str[1]=='n')&&(cmd_str[2]=='d')&&(cmd_str[3]==0)){/* if command string is "end" */
				printf("\n\nThanks for using. Bye!\n\n");
				exit(1); /* exit program */
			}
			else{
				sscanf(cmd_str, "%c %d %d %d", &cmd, &val_year, &val_month, &val_date); /* scanf
																						   values from cmd_str */
				sprintf(date_for_file, "%04d%02d%02d", val_year, val_month, val_date); /* print values in file
																						  handling form */
				sprintf(date_for_scan, "%04d %02d %02d", val_year, val_month, val_date); /* print values in
																							scan form */
				if((val_year==0)&&(cmd_str[1]==0)){ /* only command is inputed.. */
					switch(cmd){
						case 'e':
							CMD_edit(&tod_for_file[0]); /* edit mode call */
							break;
						case 'd':
							CMD_del(&tod_for_file[0]); /* delete mode call */
							break;
						case 'v':
							strftime(tod_for_scan, 14, "%Y %m %d", localtime(&now)); /* print today date in
																						scan form */
							CMD_view(&tod_for_scan[0], &tod_for_scan[0]); /* view mode call */
							break;
						case 's':
							CMD_src(); /* search mode call */
							break;
						case 'h':
							CMD_help(); /* print help page */
							break;
					}
				}
				else if((val_year!=0)&&(val_month!=0)&&(val_date!=0)){ /* inputed command and dates */
					switch(cmd){
						case 'e':
							CMD_edit(&date_for_file[0]); /* edit mode call */
							break;
						case 'd':
							CMD_del(&date_for_file[0]); /* delete mode call */
							break;
						case 'v':
							strftime(tod_for_scan, 14, "%Y %m %d", localtime(&now)); /* print today date in
																						scan form */
							CMD_view(&date_for_scan[0], &tod_for_scan[0]); /* view mode call */
							break;
					}
				}
				else{ /* else.. print error massage */
					printf("\nIncorrect Command!!\n");
					printf("Please check help page(command:h), and try again! \n\n");
					continue;
				}
			}
		}
		else if(isdigit(cmd_str[0])){/* if cmd_str[0] is digit.. */
			sscanf(cmd_str, "%d %d %d", &val_year, &val_month, &val_date);
			sprintf(date_for_file, "%04d%02d%02d", val_year, val_month, val_date); /* print values in file
																					  handling form */
			sprintf(date_for_scan, "%04d %02d %02d", val_year, val_month, val_date); /* print values in
																						scan form */
			if((val_year!=0)&&(val_month==0)&&(val_date==0)){
				prn_cal_year(val_year); /* print calender of the year */
			}
			else if((val_year!=0)&&(val_month!=0)&&(val_date==0)){
				prn_cal_month(val_year, val_month); /* print calender of the month */
			}
			else{
				strftime(tod_for_scan, 14, "%Y %m %d", localtime(&now)); /* print today date in scan form*/
				CMD_view(&date_for_scan[0], &tod_for_scan[0]); /* call view mode */
			}
		}
		else{ /* else.. print error massage */
			printf("\nIncorrect Command!!\n");
			printf("Please check help page(command:h), and try again! \n\n");
			continue;
		}
	}
	return 0;
}
