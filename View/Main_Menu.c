#include <stdio.h>
#include <string.h>

#include "Main_Menu.h"
#include "Schedule_UI.h"
#include "Studio_UI.h"
#include "Play_UI.h"
#include "Queries_Menu.h"
#include "Account_UI.h"
#include "Sale_UI.h"
#include "SalesAnalysis_UI.h"

extern char message[100]; 
extern account_t gl_CurUser; 

int mainmenuflag=1;

void Main_Menu(void) {
	char choice;
	char ch;
	do {
		system("cls");
		printf("\n\n\n"); 
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t�p�פפפפפפפ�   ��ӭ����   X��Ʊ�����ϵͳ  �פפפפפרp\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		if(mainmenuflag==1)
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
		    mainmenuflag++;
		}
		else
	    	puts(message);
		printf("\n\t\t\t[S] �����ݳ���\n");
		printf("\t\t\t[P] �����Ŀ\n");
		printf("\t\t\t[T] ��Ʊ\n");
		printf("\t\t\t[R] ��Ʊ\n");
		printf("\t\t\t[Q] ��ѯ��Ϣ\n");
		printf("\t\t\t[N] ������������\n");
		printf("\t\t\t[A] �˺Ź���˵�\n"); 
		printf("\t\t\t[E] ע��\n");
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t����������ѡ��");
		fflush(stdin);
		choice = getchar();
		switch (choice)
		{
			case 'S':
			case 's':
				Studio_UI_MgtEntry();
				mainmenuflag--;
				break;
			case 'P':
			case 'p':
				Play_UI_MgtEntry(0);
				break;
			case 'Q':
			case 'q':
				Queries_Menu();
				mainmenuflag--;
				break;
			case 'T':
			case 't':
				Sale_UI_MgtEntry();
				strcpy(message,"\n\t\t\t��Ʊ������δ��ͨ�������ڴ���");
				break;
			case 'R':
			case 'r':
				Sale_UI_ReturnTicket();
				strcpy(message,"\n\t\t\t��Ʊ������δ��ͨ�������ڴ���");
				break;
			case 'N':
			case 'n':
				SalesAanalysis_UI_MgtEntry();
				break;
			case 'A':
			case 'a':
				Account_UI_MgtEntry();
				mainmenuflag--;
				break;
			case 'E':
			case 'e':
				printf("\n\t\t\tȷ��ע����[Y/y]ȷ��[������ĸ]ȡ����");
				fflush(stdin);
				scanf("%c",&ch);
				if(ch!='y')
				{
					strcpy(message,"\n\t\t\tע��ʧ��"); 
					Main_Menu();
				    break;
				}
			    mainmenuflag--;
			    main();
			    break;
		}
	} while ('E' != choice && 'e' != choice);
}

