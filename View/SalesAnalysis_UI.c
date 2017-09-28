/*
 * SalesAnalysis_UI.c
 *	רҵˮӡ���ԣ����� 
 *  Created on: 2015��6��20��
 *      Author: ���� 
 */
#include "SalesAnalysis_UI.h"
#include "../Common/list.h"
#include "../Common/common.h"
#include "../Service/SalesAnalysis.h"
#include <conio.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

//�ⲿ����gl_CurUser ���ڴ洢��¼�û���Ϣ
extern account_t gl_CurUser;
extern char message[100];
int saleflag=1;

//�����ҳ������ҳ���СΪ5
static const int SALESANALYSIS_PAGE_SIZE = 5;

//��Ժ�������а���,������ʾ��ֹĿǰ��Ժ��ӰƱ�����а�
void SalesAnalysis_UI_BoxOffice() {
	salesanalysis_list_t  list;
	salesanalysis_node_t  *pos;
	/*����һ����ҳ��*/
	Pagination_t pageing;
	/*��ʼ����������*/ 
	List_Init(list,salesanalysis_node_t);
	//���÷�ҳ��С
	pageing.totalRecords=Salesanalysis_Srv_StaticSale(list); 
	/*���÷�ҳ��ʾҳ���С*/
	pageing.pageSize =SALESANALYSIS_PAGE_SIZE;  
	Salesanalysis_Srv_StaticSale(list);//ͳ���������ݣ����������۷�������
	printf("\n\t\t\t��ѡ����Ӧ����\n");
	char choice;
	do{
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t[P] ��ʾ��һҳ��ĿƱ��������Ϣ\n");
		printf("\t\t\t[N] ��ʾ��һҳ��ĿƱ��������Ϣ\n");
		printf("\t\t\t[R] �˳�\n");
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t����������ѡ��"); 
		fflush(stdin);
		choice=getchar();
		switch(choice){
			case 'P':
			case 'p':
			    break;
			case 'n':
			case 'N':
			    break;
			case 'r':
			case 'R':{
				choice='E';
				break;
			}
		}  
	}while(choice!='E');	
}

//��ʾ��ƱԱ�ڸ��������������Ʊ���
void SalesAnalysis_UI_StatSale(int usrID, user_date_t stDate, user_date_t endDate){
	float sale;
	account_t user;
	user.id=usrID;
	sale=Salesanalysis_Srv_CompSaleVal(usrID,stDate,endDate);
	Account_Srv_FetchByID(user.id,&user);
	printf("��%d-%d-%d��%d-%d-%d�ڼ����۶�Ϊ%d:\n",stDate.year,stDate.month,stDate.day,endDate.year,endDate.month,endDate.day,sale);
}
//���۷�����ں�������ʾ�˵����˵�����"������ʾ��ֹĿǰ��Ժ��ӰƱ�����а�"������ʾ���ѯ������ƱԱ��Ʊ�������
//����ѯ������������ĳ��ƱԱ��Ʊ�����
void SalesAanalysis_UI_MgtEntry() {
	
	user_date_t stDate,endDate;
	account_t user; 
	char choice;
	do{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t�p�פפפפפפפפפפ�  �������ݷ��� �פפפפפפפפפפרp\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		if(saleflag==1)
		{
			strcpy(message,"\n\t\t\t��ѡ��"); 
			puts(message);
			saleflag++;
		}
		else
		    puts(message);
		printf("\n\t\t\t[B] ��ĿƱ�����а�\n");
		printf("\t\t\t[D] ��ѯԱ���ڸ��������������۶����\n");
		printf("\t\t\t[S] ��ѯԱ���ڸ�������������Ʊ���\n");
		printf("\t\t\t[R] ����\n");
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t����������ѡ��");
		/*ˢ�����뻺����*/
		fflush(stdin);
		scanf("%c",&choice);
		switch(choice)
		{
			case 'B': 
			case 'b':
				SalesAnalysis_UI_BoxOffice();
				break;
			case 'D':
			case 'd':
				if(gl_CurUser.type==USR_CLERK)
					SalesAnalysis_UI_StatSale(gl_CurUser.id,stDate,endDate);//���� 
				else
 					{
 						printf("\t\t\t��������ƱԱ������");
 						fflush(stdin);
 						char UsrName[100];
						scanf("%s",UsrName);		
						if(!Account_Srv_FetchByName(UsrName,&user))
							strcpy(message,"\n\t\t\t����ƱԱ�����ڡ�\n");
						else
							SalesAnalysis_UI_StatSale(user.id,stDate,endDate);//����
					}
				break;
			case 'S':
			case 's':
				if(gl_CurUser.type==USR_MANG)
				{
					char UsrName[100];
					printf("��������ƱԱ������\n");
					scanf("%s",UsrName);
						/*ˢ�����뻺����*/ 
						fflush(stdin);
					if(!Account_Srv_FetchByName(UsrName,&user))
						printf("�û���������!!\n");
					else
					{
						printf("\t\t\t�������Ŀ��ӳʱ��(��ʽΪ:��-��-��):");
						fflush(stdin);
						scanf("%d-%d-%d",&stDate.year,&stDate.month,&stDate.day);
						printf("\t\t\t�������Ŀ��ӳʱ��(��ʽΪ:��-��-��):");
						fflush(stdin);
						while(scanf("%d-%d-%d",&endDate.year,&endDate.month,&endDate.day))
						{
							printf("\t\t\t������ĸ�ʽ�д����밴�� ��-��-�� ����д��");
							printf("\t\t\t������������ӳʱ�䣺");
						}
						SalesAnalysis_UI_StatSale(user.id,stDate,endDate);
					}
				}
				else
				{
					printf("\n\t\t\t����Ҫ���ߵ�Ȩ�޲��ܽ��д˲���!\n"); 
					break;
				}
			default:
				strcpy(message,"\n\t\t\t������������������ѡ��");
				break; 
		 } 
	}while(choice!='R' && choice!='r' );
}



