/*
 * Studio_UI.c
 *
 *  Created on: 2015��4��24��
 *      Author: Administrator
 */
#include "Studio_UI.h"

#include "../Common/list.h"
#include "../Service/studio.h"
#include "../Service/seat.h"
#include "../Service/EntityKey.h"
#include "Seat_UI.h"

static const int STUDIO_PAGE_SIZE = 5;

int studioflag=1;
extern char message[100];

#include <stdio.h>
#include <string.h>

void Studio_UI_MgtEntry(void) {
	int i, id, r;
	char choice;
	char ch; 

	studio_list_t head;
	studio_node_t *pos;
	Pagination_t paging;

	List_Init(head, studio_node_t);
	paging.offset = 0;
	paging.pageSize = STUDIO_PAGE_SIZE;

	//��������
	paging.totalRecords = Studio_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t�p�פפפפפפפפפפ�   �ݳ�����Ϣ  �פפפפפפפפפפרp\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		if(studioflag==1)
		{
			strcpy(message,"\n\t\t\t�ݳ�����Ϣ���¡�");
			puts(message);
			studioflag++;
		}
		else
		    puts(message);
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\tID   �ݳ�����                ��λ����     ��λ����     ��λ����\n"); 
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
		//��ʾ����
		for (i = 0, pos = (studio_node_t *) (paging.curPos);
				pos != head && i < paging.pageSize; i++) {
			printf("\t\t\t%-5d%-24s%-13d%-13d%-8d\n", pos->data.id,
					pos->data.name, pos->data.rowsCount, pos->data.colsCount,
					pos->data.seatsCount);
			pos = pos->next;
		}
		printf("\n\t\t\t------- �ܹ�%2d����¼ ------------- ҳ���� %2d/%2d ---------------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[P]��һҳ|[N]��һҳ|[A]���|[D]ɾ��|[U]����|[S]��λ��Ϣ|[R]����\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t����������ѡ��");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
		switch (choice) {
		case 'a':	
		case 'A':
			if (r=Studio_UI_Add()) //�£��������һҳ��ʾ
			{
				paging.totalRecords = Studio_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, studio_node_t);
				sprintf(message,"\n\t\t\t�ɹ������%2d���ݳ�����",r);
			}
			break;
		case 'd':
		case 'D':
			printf("\t\t\t�������ݳ���ID��");
			while(scanf("%d",&id)!=1)
			{
				printf("\t\t\t������Ĳ�������\n");
				printf("\t\t\t���������룺");
				while((ch=getchar())!='\n')
				    continue; 
			}
			if(Studio_UI_Delete(id))
			{	//������������
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
				sprintf(message,"\n\t\t\t�ɹ�ɾ����%2d���ݳ�����",id);
			}
			else
			{
				strcpy(message,"\n\t\t\t���ݳ����������ڡ�");
			}
			break;
		case 'u':
		case 'U':
			printf("\t\t\t�������ݳ���ID��");
			while(scanf("%d",&id)!=1)
			{
				printf("\t\t\t������Ĳ�������\n");
				printf("\t\t\t���������룺");
				while((ch=getchar())!='\n')
				    continue; 
			}
			if (Studio_UI_Modify(id)) {	//������������
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
				strcpy(message,"\n\t\t\t�޸��ݳ����ɹ���");
			}
			else
			    strcpy(message,"\n\t\t\t���ݳ����������ڡ�");
			break;
		case 's':
		case 'S':
			printf("\t\t\t�������ݳ���ID��");
			while(scanf("%d",&id)!=1)
			{
				printf("\t\t\t������Ĳ�������\n");
				printf("\t\t\t���������룺");
				while((ch=getchar())!='\n')
				    continue; 
			}
			Seat_UI_MgtEntry(id);
			paging.totalRecords = Studio_Srv_FetchAll(head);
			List_Paging(head, paging, studio_node_t);
			break;
		case 'p':
		case 'P':
			if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, studio_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, studio_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//�ͷ�����ռ�
	List_Destroy(head, studio_node_t);
}

int Studio_UI_Add(void) {
	studio_t rec;
	int i=1;
	int newRecCount = 0;
	char choice;
	char ch;

	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	    printf("\t\t\t�p�פפפפפפפפפפ�   �����ݳ���  �פפפפפפפפפפרp\n");
	    printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		printf("\n\t\t\t�������%d���ݳ�����\n\n",i++);
		printf("\t\t\t�ݳ�������");
		fflush(stdin);
		gets(rec.name);
		printf("\t\t\t�ݳ�����λ������");
		while(scanf("%d",&(rec.rowsCount))!=1)
		{
			printf("\t\t\t������Ĳ�������\n");
			printf("\t\t\t���������룺");
			while((ch=getchar())!='\n')
			    continue; 
		}
		printf("\t\t\t�ݳ�����λ������");
		while(scanf("%d",&(rec.colsCount))!=1)
		{
			printf("\t\t\t������Ĳ�������\n");
			printf("\t\t\t���������룺");
			while((ch=getchar())!='\n')
			    continue; 
		}
		rec.seatsCount = rec.rowsCount * rec.colsCount;
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		//��ȡ����
		rec.id = EntKey_Srv_CompNewKey("Studio");
		if (Studio_Srv_Add(&rec))
		{
			newRecCount += 1;
			printf("\t\t\t�ݳ�����ӳɹ���\n");
		}
		else
			printf("\t\t\t�ݳ������ʧ�ܣ�\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[A]��Ӹ���|[R]����\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		fflush(stdin);
		printf("\n\t\t\t����������ѡ��"); 
		scanf("%c", &choice);
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

int Studio_UI_Modify(int id) {
	studio_t rec;
	int rtn = 0;
	int newrow, newcolumn;
	seat_list_t list;
	int seatcount;
	/*Load record*/
	if (!Studio_Srv_FetchByID(id, &rec)) {
		return 0;
	}
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t�p�פפפפפפפפפפ�   �����ݳ���  �פפפפפפפפפפרp\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
	printf("\n\t\t\t�ݳ���ID--%d\n", rec.id);
	printf("\n\t\t\t�ݳ�����--[%s]:", rec.name);
	fflush(stdin);
	gets(rec.name);
	List_Init(list, seat_node_t);
	seatcount = Seat_Srv_FetchByRoomID(list, rec.id);
	if(seatcount){
		do{			//�����λ�ļ���������λ��Ϣ������µ����б������ǰ�󣬷����������
			printf("\n\t\t\t��λ�������� >= [%d]:", rec.rowsCount);
			scanf("%d", &(newrow));
			printf("\n\t\t\t��λ�������� >= [%d]:", rec.colsCount);
			scanf("%d", &(newcolumn));
		}while(	newrow<rec.rowsCount||newcolumn<rec.colsCount);
		rec.rowsCount=newrow;
		rec.colsCount=newcolumn;
		rec.seatsCount=seatcount;
	}
	else{
		printf("\t\t\t��λ������");
		scanf("%d", &rec.rowsCount);
		printf("\t\t\t��λ������");
		scanf("%d", &rec.colsCount);
		rec.seatsCount=0;
	}

	printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");

	if (Studio_Srv_Modify(&rec))
	{
		rtn = 1;
	}
	getchar();
	return rtn;
}

int Studio_UI_Delete(int id) {
	int rtn = 0;
	if (Studio_Srv_DeleteByID(id))
	{
		//��ɾ����ӳ��ʱ��ͬʱ���ݷ�ӳ��idɾ����λ�ļ��е���λ
		Seat_Srv_DeleteAllByRoomID(id); 
		rtn = 1;
	}
	getchar();
	return rtn;
}

