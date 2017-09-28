/*
* File name:  Play_UI.c
* File ID:	  TTMS_SSF_Play_UI_Sour
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/


#include "Play_UI.h"
#include "Schedule_UI.h"

#include "../Common/list.h"
#include "../Service/play.h"
#include "../Service/EntityKey.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Play_UI_ShowList(play_list_t list, Pagination_t paging);
void Play_UI_MgtEntry(int flag);
int Play_UI_Add(void);
int Play_UI_Modify(int id);
int Play_UI_Delete(int id);
int Play_UI_Query(int id);
 
	/*
	 * Function:    Play_UI_ShowList
	 * Function ID:	TTMS_SCU_Play_UI_Show
	 * Description: ���б�ģʽ��ʾ��Ŀ��Ϣ
	 * Input:       list��Ŀ��Ϣ�����ͷָ�룬paging��ҳ���ò���
	 * Output:      ���о�Ŀ����Ϣ
	 * Return:      ���ز��ҵ��ļ�¼��Ŀ
	 */

static void ShowListByPage(play_node_t *list,int listSize)
{
	int pageSize=5,i;
	Pagination_t paging;
	play_node_t *p;
	char choice;
	paging.pageSize=pageSize;
	paging.totalRecords=listSize;
	Paging_Locate_FirstPage(list,paging);
	do{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t�p�פפפפפפפפפפפ�   ��Ŀ��Ϣ  �פפפפפפפפפפרp\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		printf("\n\n\n");
		printf("\t\t\t%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n","��ĿID��","��Ŀ����","��Ŀ����","��Ŀ��Դ��","��Ŀ����","�ݳ�ʱ��(����)","��ӳ����","��������","Ʊ��");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("%5d%32s%8s%10s%3s%7s%13s%13s%5s\n",p->data.id,p->data.name,p->data.type,p->data.area,p->data.rating,p->data.duration,p->data.start_date,p->data.end_date,p->data.price);
		printf("--Total Records:%2d---------Page%2d/%2d--\n\n",paging.totalRecords,Pageing_CurPage(paging),Pageing_TotalPages(paging));
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[F]��һҳ|[p]��һҳ|[N]��һҳ|[L]���һҳ|[e]�˳�\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("������ѡ�");
		fflush(stdin);
		scanf("%c",&choice);
		switch(choice)
		{
			case 'f':
			case 'F':
				Paging_Locate_FirstPage(list,paging);
				break;
			case 'p':
			case 'P':
	            if(1<Pageing_CurPage(paging))
				{
		    		Paging_Locate_OffsetPage(list,paging,-1,play_node_t);
		    	}
	    		break;	
			case 'n':   
			case 'N':
				if(Pageing_TotalPages(paging)>Pageing_CurPage(paging))
				{
					Paging_Locate_OffsetPage(list,paging,-1,play_node_t);
				}
				break;
			case 'l':
			case 'L':
				Paging_Locate_LastPage(list,paging,play_node_t);
				break;
		}
	}while(choice!='e'&&choice!='E'); 
}
int CreateList_Head(play_list_t list){
		int i=0;
		play_node_t*p;
		for(i =0;i<100;i++)
		{
			p = (play_node_t*)malloc(sizeof(play_node_t));
			if(!p)
				break;
			List_AddHead(list,p);
		} 
		return i;
	}
void Play_UI_ShowList(play_list_t list,Pagination_t paging){
	int size;
	ShowListByPage(list,size);
}

/*
 * Function:    Play_UI_MgtEntry
 * Function ID:	TTMS_SCU_Play_UI_MgtEnt
 * Description: ��Ŀ��Ϣ�������
 * Input:       flagΪ0���������ҳ�棬flagΪ1�����ѯ����
 * Output:      ��Ŀ�������
 * Return:      ��
 */
void Play_UI_MgtEntry(int flag)
{
	int i,j,fg;
	play_list_t list;
	Pagination_t paging;
	char ch;
	switch(flag)
	{
		case 0:
			system("cls");
			printf("\n\n\n");
			printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
			printf("\t\t\t�p�פפפפפפפפפפפ�   �����Ŀ  �פפפפפפפפפפרp\n");
			printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
			printf("\n\n\n");
			printf("\t\t\t[A] ��Ӿ�Ŀ\n");
			printf("\t\t\t[U] �޸ľ�Ŀ\n");
			printf("\t\t\t[D] ɾ����Ŀ\n");
			printf("\t\t\t[M] �ݳ��ƻ�����\n");
			printf("\t\t\t[����] ����\n");
			printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
			printf("\n\t\t\t������ѡ�");
			fflush(stdin);
			scanf("%c",&ch);
			toupper(ch);
			switch(ch)
			{
				case 'A':
				case 'a':
					Play_UI_Add();
					break;
				case 'U':
				case 'u':
					printf("\t\t\t������Ҫ�޸ĵľ�Ŀ���:");
					while(scanf("%d",&j)!=1)
					{
						printf("\t\t\t������Ĳ�������\n");
						printf("\t\t\t���������룺");
						while((ch=getchar())!='\n')
						    continue; 
					}
					Play_UI_Modify(j);
					break;
				case 'D':
				case 'd':
					printf("\t\t\t������Ҫɾ���ľ�Ŀ���:");
					while(scanf("%d",&j)!=1)
					{
						printf("\t\t\t������Ĳ�������\n");
						printf("\t\t\t���������룺");
						while((ch=getchar())!='\n')
						    continue; 
					}
					Play_UI_Delete(j);
					break;
				case 'M':
				case 'm':
					printf("\t\t\t������Ҫ��ѯ���ݳ��ƻ�ID��");
					while(scanf("%d",&j)!=1)
					{
						printf("\t\t\t������Ĳ�������\n");
						printf("\t\t\t���������룺");
						while((ch=getchar())!='\n')
						    continue; 
					}
					Schedule_UI_MgtEntry(j);
					break;
				default:
					Main_Menu();
					break;
			}
			Play_UI_MgtEntry(0);
			break;
		case 1:
			system("cls");
			printf("\n\n\n");
			printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
			printf("\t\t\t�p�פפפפפפפפפפפ�   ��ѯ��Ŀ  �פפפפפפפפפפרp\n");
			printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
			printf("\n\n\n");
			printf("\t\t\t�ù�����δʵ��\n");
			printf("\t\t\t������Ҫ��ѯ�ľ�Ŀ���:");
			while(scanf("%d",&j)!=1)
			{
				printf("\t\t\t������Ĳ�������\n");
				printf("\t\t\t���������룺");
				while((ch=getchar())!='\n')
				    continue;
			}
			Main_Menu();
//			Play_UI_Query(j);
	        break;
	    default:
	        break;
	}
	Main_Menu();
}


/*
 * Function:    Play_UI_Add
 * Function ID:	TTMS_SCU_Play_UI_Add
 * Description: ���һ����Ŀ��Ϣ
 * Input:       ��
 * Output:      ������Ϣʱ�ĸ�����ʾ
 * Return:      ��ӵļ�¼��
 */
int Play_UI_Add(void)
{
	play_t rec;
	int i= 0,temp;
	char ch,choice;
    system("cls");
	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t�p�פפפפפפפפפפפ�   ��Ӿ�Ŀ  �פפפפפפפפפפרp\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		printf("\n\t\t\t������ӵ�%d����Ŀ\n\n",i+1);
		printf("\t\t\t��ϢID��:");
		fflush(stdin);
		while(scanf("%d", &(rec.id))!=1)
		{
			printf("\t\t\t������Ĳ�������\n");
			printf("\t\t\t���������룺");
			while((ch=getchar())!='\n')
			    continue;
		}
		printf("\t\t\t��Ŀ����:");
		scanf("%s",rec.name);
		printf("\t\t\t��Ŀ����:");
		scanf("%s",&temp);
		rec.type=(play_type_t)(temp);
		printf("\t\t\t��Ŀ��Դ��:");
		scanf("%s",rec.area);
		printf("\t\t\t��Ŀ����:");
		scanf("%s",&temp);
		rec.rating=(play_rating_t)(temp);
		printf("\t\t\t�ݳ�ʱ��(����):");
		while(scanf("%d",&rec.duration)!=1)
		{
			printf("\t\t\t������Ĳ�������\n");
			printf("\t\t\t���������룺");
			while((ch=getchar())!='\n')
			    continue;
		}
		printf("\t\t\t��ӳ����:");
		scanf("%s",rec.start_date);
		printf("\t\t\t��������:");
		scanf("%s",rec.end_date);
		printf("\t\t\tƱ��:");
		scanf("%s",&rec.price);
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");

		//��ȡ����
		rec.id = EntKey_Srv_CompNewKey("play");

		if (Play_Srv_Add(&rec)!=0)
		{
			i += 1;
			printf("\t\t\t��ӳɹ�!");
		}
		else
		printf("\t\t\t���ʧ��!");
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[A]��Ӹ���|[����]����\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t����������ѡ��");
		fflush(stdin);
		scanf("%c",&choice);
	} while ('A' == choice || 'a' == choice);
	return i;
}

	
/*
 * Function:    Play_UI_Modify
 * Function ID:	TTMS_SCU_Play_UI_Mod
 * Description: ���¾�Ŀ��Ϣ
 * Input:       �����µľ�ĿID��
 * Output:      ������Ϣʱ�ĸ�����ʾ
 * Return:      ���µľ�Ŀ��Ϣ����0��ʾδ�ҵ���1��ʾ�ҵ�������
 */
int Play_UI_Modify(int id){
	play_t rec;
	int rtn = 0,i,temp;
	play_list_t list;
	int seatcount;
	play_t *re;
    system("cls");
	/*Load record*/
	if (Play_Srv_FetchByID(id, &rec)!=1) {
		printf("��Ŀ������!\n");
		return 0;
	}
	printf("\n\n\n");
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t�p�פפפפפפפפפפפ�   ��Ŀ��Ϣ  �פפפפפפפפפפרp\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
	printf("\n\n\n");
	printf("%-5s%-32s%-8s%-10s%-3s%-7s%-13s%-13s%-5s\n","1","2","3","4","5","6","7","8","9");
	printf("\t\t\t%10s%10s%10s%10s%10s%10s%10s%10s%10s\n","��ϢID��","��Ŀ����","��Ŀ����","��Ŀ��Դ��","��Ŀ����","�ݳ�ʱ��(����)","��ӳ����","��������","Ʊ��");
	printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
	printf("%5d%32s%8s%10s%3s%7s%13s%13s%5s\n",rec.id,rec.name,rec.type,rec.area,rec.rating,rec.duration,rec.start_date,rec.end_date,rec.price);
	fflush(stdin);
	scanf("��������Ҫ�޸ĵ�ѡ��(����0�˳�)��%d",&i);
	do{
		switch(i)
		{
			case 1:printf("��ϢID��:");
				scanf("%d", &(rec.id));
				break;
			case 2:	printf("��Ŀ����:");
				scanf("%s",rec.name);
				break;	
			case 3:printf("��Ŀ����:");
				scanf("%s",&temp);
				rec.type=(play_type_t)(temp);
				break;
			case 4:	printf("��Ŀ��Դ��:");
				scanf("%s",rec.area);
				break;
			case 5:printf("��Ŀ����:");
				scanf("%s",&temp);
				rec.rating=(play_rating_t)(temp);
				break;	
			case 6:printf("�ݳ�ʱ��(����):");
				scanf("%s",&rec.duration);
				break;	
			case 7:	printf("��ӳ����:");
				scanf("%s",rec.start_date);
				break;
			case 8:printf("��������:");
				scanf("%s",rec.end_date);
				break;
			case 9:	printf("Ʊ��:");
				scanf("%s",&rec.price);
				break;
		}
	}while((scanf("��������Ҫ�޸ĵ�ѡ��(����0�˳�)��%d",&i))!=0);
	printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
	if (Play_Srv_Modify(&rec)) 
	{
		rtn = 1;
		printf("���ʧ��\n");
	}
	else
		printf("��ӳɹ�\n");
	return rtn;
}


/*
 * Function:    Play_UI_Delete
 * Function ID:	TTMS_SCU_Play_UI_Del
 * Description: ����ID��ɾ����Ŀ��Ϣ
 * Input:       ��ɾ���ľ�ĿID��
 * Output:      ��ʾɾ���Ƿ�ɹ�
 * Return:      0��ʾɾ��ʧ�ܣ�1��ʾɾ���ɹ�
 */
int Play_UI_Delete(int id){
	int rtn = 0;
    system("cls");
	if(Play_Srv_DeleteByID(id)==1){
		printf("ɾ���ɹ��������������!\n");
		rtn = 1;
	}
	 else {
		printf("�þ�Ŀ�����ڣ������������!\n");
	}

	getchar();
	return rtn;

}

/*
 * Function:    Play_UI_Query
 * Function ID:	TTMS_SCU_Play_UI_Qry
 * Description: ����ID�Ų�ѯ��Ŀ��Ϣ
 * Input:       �����ҵľ�ĿID��
 * Output:      ���ҵ��ľ�Ŀ��Ϣ
 * Return:      0��ʾδ�ҵ���1��ʾ�ҵ���
 */
int Play_UI_Query(int id){
	
	return 0;
}
