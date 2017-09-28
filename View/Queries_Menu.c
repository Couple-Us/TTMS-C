#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "Account_UI.h"
#include "Queries_Menu.h"
#include "Schedule_UI.h"
#include "Studio_UI.h"
#include "Play_UI.h"

extern char message[100];
extern account_t gl_CurUser; 

int queriesflag=1;

void Queries_Menu(void){
	char choice;
	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t�p�פפפפפפפפפפפ�   ��Ϣ��ѯ  �פפפפפפפפפפרp\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		if(queriesflag==1)
		{
			switch(gl_CurUser.type)
			{
				case 0:
					strcpy(message,"\n\t\t\t�����û�,���á�");
					break;
				case 1:
				    strcpy(message,"\n\t\t\t����Ա,���á�");
				    break;
				case 2:
					strcpy(message,"\n\t\t\t����,���á�");
					break;
				case 9:
					strcpy(message,"\n\t\t\tϵͳ����Ա,���á�");
					break;
				default:
				    strcpy(message,"\n\t\t\t���á�");
				    break;
			}
		    strcat(message,"��ӭʹ���û��˺Ź���ģ�顣");
		    puts(message);
		    queriesflag++;
		}
		else
	    	puts(message);
		printf("\t\t\t[S]��ѯ�ݳ���\n");
		printf("\t\t\t[P]��ѯ��Ŀ\n");
		printf("\t\t\t[T]��ѯƱ\n");
		printf("\t\t\t[C]��ѯ�ݳ��ƻ�\n");
		printf("\t\t\t[R]������һ��\n");
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t����������ѡ��");
		fflush(stdin);
		choice = getchar();
		switch (choice) {
		case 'S':
		case 's'://Studio_query;
		    Studio_UI_MgtEntry();
		    queriesflag--;
			break;
		case 'P':
		case 'p':
			Play_UI_MgtEntry(1);
			queriesflag--;
			break;
		case 'T':
		case 't': //Ticket_query;
		    strcpy(message,"\n\t\t\t��ѯƱģ����δ��ͨ");
		    Queries_Menu();
			break;
		case 'C':
		case 'c':
			Schedule_UI_ListAll();
			strcpy(message,"\n\t\t\t��ѯ�ݳ��ƻ���δ��ͨ");
		    Queries_Menu();
			break;
		}
	} while ('R' != choice && 'r' != choice);
	}
