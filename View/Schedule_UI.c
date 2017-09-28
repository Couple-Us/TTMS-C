/*
* File name:  Schedule_UI.c
* File ID:	  TTMS_SSF_Schedule_UI_Sour
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/


#include "Schedule_UI.h"
#include "Play_UI.h"

#include "../Common/list.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"


//static const int SCHEDULE_PAGE_SIZE = 5;

#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

	/*
	 * Function:    Schedule_UI_ListAll
	 * Function ID:	TTMS_SCU_Schedule_UI_List
	 * Description: ��ʾ���е��ݳ��ƻ���Ϣ,���в�ѯ��
	 * Input:       ��
	 * Output:      ���о�Ŀ����Ϣ
	 * Return:      ��
	 */
void Schedule_UI_ListAll(void) {
	int i;
	schedule_list_t head;          //˫������Ķ���  
	schedule_node_t *pos;          //˫�������һ�����  
	char choice;
	Pagination_t paging;         
	List_Init(head, schedule_node_t);        //����
	paging.offset = 0;       //��ʼ��  ��¼ 
	paging.pageSize = SCHEDULE_PAGE_SIZE;
	//��������
	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
    do{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t�p�פפפפפפפפפפ�    �ݳ��ƻ���   �פפפפפפפפפרp\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		printf("\n\n\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t%-8s%-8s%-10s%-15s%-14s%-8s\n", "�ƻ�ID��", "��ĿID��", "��ӳ��ID��","�ݳ�����", "�ݳ�ʱ��","��λ����");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
		//��ʾ����
		for (i = 0, pos = (schedule_node_t *) (paging.curPos);
				pos != head && i < paging.pageSize; i++) {
			printf("\t\t\t%-8d%-8d%-10d%-11d��%02d��%02d��%-10dʱ%02d��%02d��%-8d\n", pos->data.id,
					pos->data.play_id, pos->data.studio_id, pos->data.date.year,pos->data.date.month,pos->data.date.day,
					pos->data.time.hour,pos->data.time.minute,pos->data.time.second,pos->data.seat_count);
			pos = pos->next;
		}
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t------- �ܹ�%2d����¼ ------------- ҳ���� %2d/%2d ---------------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t\t[F]��һҳ|[p]��һҳ|[N]��һҳ|[L]���һҳ|[e]�˳�\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t������ѡ�");
		fflush(stdin);
		scanf("%c",&choice);
//		switch(choice)
//		{
//			case 'f':
//			case 'F':
//				Paging_Locate_FirstPage(list,paging);
//				break;
//			case 'p':
//			case 'P':
//	            if(1<Pageing_CurPage(paging))
//				{
//		    		Paging_Locate_OffsetPage(list,paging,-1,play_node_t);
//		    	}
//	    		break;	
//			case 'n':   
//			case 'N':
//				if(Pageing_TotalPages(paging)>Pageing_CurPage(paging))
//				{
//					Paging_Locate_OffsetPage(list,paging,-1,play_node_t);
//				}
//				break;
//			case 'l':
//			case 'L':
//				Paging_Locate_LastPage(list,paging,play_node_t);
//				break;
//		}
	}while(choice!='e'&&choice!='E'); 
}

/*
 * Function:    Schedule_UI_Add
 * Function ID:	TTMS_SCU_Schedule_UI_Add
 * Description: ���һ���ݳ��ƻ���Ϣ
 * Input:       ��ؾ�Ŀ��ID��
 * Output:      ������Ϣʱ�ĸ�����ʾ
 * Return:      ��ӵļ�¼��
 */
int Schedule_UI_Add(int play_id) {  
   
	schedule_t  rec;
	int newRecCount = 0;
	char choice;
	char ch;

	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t�p�פפפפפפפפפ�   ����µ��ݳ��ƻ�  �פפפפפפפפרp\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		printf("\n\n\n");
		printf("\t\t\t��ĿID��:");
		fflush(stdin);
		while(scanf("%d", &(rec.play_id))!=1)
		{
			printf("\t\t\t������Ĳ�������\n");
			printf("\t\t\t���������룺");
			while((ch=getchar())!='\n')
			    continue;
		}
		printf("\t\t\t��ӳ��ID�ţ�"); 
		fflush(stdin);
		while(scanf("%d", &(rec.studio_id))!=1)
		{
			printf("\t\t\t������Ĳ�������\n");
			printf("\t\t\t���������룺");
			while((ch=getchar())!='\n')
			    continue;
		}
		printf("\t\t\t�ݳ�����\n"); 
		printf("\t\t�꣺");
		while(scanf("%d", &(rec.date.year))!=1)
		{
			printf("\t\t\t������Ĳ�������\n");
			printf("\t\t\t���������룺");
			while((ch=getchar())!='\n')
			    continue;
		}
		printf("\t\t�£�");
		while(scanf("%d", &(rec.date.month))!=1)
		{
			printf("\t\t\t������Ĳ�������\n");
			printf("\t\t\t���������룺");
			while((ch=getchar())!='\n')
			    continue;
		}
		printf("\t\t��:"); 
		while(scanf("%d", &(rec.date.day))!=1)
		{
			printf("\t\t\t������Ĳ�������\n");
			printf("\t\t\t���������룺");
			while((ch=getchar())!='\n')
			    continue;
		}
		printf("\t\t\t�ݳ�ʱ��:");
		printf("\n\t\t\tʱ��");
		while(scanf("%d", &(rec.time.hour))!=1)
		{
			printf("\t\t\t������Ĳ�������\n");
			printf("\t\t\t���������룺");
			while((ch=getchar())!='\n')
			    continue;
		}
		printf("\n\t\t\t�֣�");
		while(scanf("%d", &(rec.time.minute))!=1)
		{
			printf("\t\t\t������Ĳ�������\n");
			printf("\t\t\t���������룺");
			while((ch=getchar())!='\n')
			    continue;
		}
		printf("\n\t\t\t��:"); 
		while(scanf("%d", &(rec.time.second))!=1)
		{
			printf("\t\t\t������Ĳ�������\n");
			printf("\t\t\t���������룺");
			while((ch=getchar())!='\n')
			    continue;
		}
		printf("\t\t\t��λ����:\n"); 
		scanf("%d",&(rec.seat_count));
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		//��ȡ����
		rec.id = EntKey_Srv_CompNewKey("Schedule");   //������һ��id 
		if (Schedule_Srv_Add(&rec)) {
			newRecCount ++;
			printf("\t\t\t�µ��ݳ��ƻ���ӳɹ���\n");
		} else
			printf("\t\t\t�µ��ݳ��ƻ����ʧ��!\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[A]�������|[R]����\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t����������ѡ��");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

/*
 * Function:    Schedule_UI_Modify
 * Function ID:	TTMS_SCU_Schedule_UI_Mod
 * Description: ����ID�Ÿ����ݳ��ƻ���Ϣ
 * Input:       �����µľ�ĿID��
 * Output:      ������Ϣʱ�ĸ�����ʾ
 * Return:      ���µľ�Ŀ��Ϣ����0��ʾδ�ҵ���1��ʾ�ҵ�������
 */
int Schedule_UI_Modify(int id){
	schedule_t rec;
	int choice=0;
	int rtn = 0;
	if (!Schedule_Srv_FetchByID(id, &rec)) {
		printf("����ݳ��ƻ������˳�!\n�밴 [Enter] �˳�!\n");
		getchar();
		return 0;
	}
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t�p�פפפפפפפפפ�   �޸��ݳ��ƻ���Ϣ  �פפפפפפפפרp\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
	printf("\n\t\t\t�ݳ��ƻ�ID:%d\n", rec.id);
	printf("\t\t\t�ݳ���ĿID[%d]��Ϊ:", rec.play_id);
	fflush(stdin);
	scanf("%d",&(rec.play_id));fflush(stdin);
	
	printf("\t\t\t�ݳ��ķ�ӳ��ID[%d]��Ϊ:",rec.studio_id);
	fflush(stdin);
	scanf("%d",&(rec.studio_id));fflush(stdin);
	
	printf("\t\t\t�ݳ�����  %d �� %d �� %d �� ��Ϊ:",rec.date.year,rec.date.month,rec.date.day);
	printf("\n\t\t\t��:");scanf("%d",&(rec.date.year));fflush(stdin);
	printf("\n\t\t\t��:");scanf("%d",&(rec.date.month));fflush(stdin);
	printf("\n\t\t\t��:");scanf("%d",&(rec.date.day ));fflush(stdin);
	
	printf("\t\t\t�ݳ�ʱ�� %d ʱ %d �� %d �� ��Ϊ:",rec.time.hour,rec.time.minute,rec.time.second);
	printf("\n\t\t\tʱ:");scanf("%d",&(rec.time.hour));fflush(stdin);
	printf("\n\t\t\t��:");scanf("%d",&(rec.time.minute));fflush(stdin);
	printf("\n\t\t\t��:");scanf("%d",&(rec.time.second));fflush(stdin);
	
	printf("\t\t\t��λ����[%d]��Ϊ:",rec.seat_count);
	scanf("%d",&(rec.seat_count));fflush(stdin);
	
	printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");

	if (Schedule_Srv_Modify(&rec)) {
		rtn = 1;
		printf("\t\t\t�ݳ����ݸ��³ɹ�!\n�밴 [Enter] ����!\n");
	} else
		printf("\t\t\t�ݳ����ݸ���ʧ��!\n�밴 [Enter] ����!\n");

	getchar();
	return rtn;
}

/*
 * Function:    Schedule_UI_Delete
 * Function ID:	TTMS_SCU_Schedule_UI_Del
 * Description: ����ID��ɾ���ݳ��ƻ���Ϣ
 * Input:       ��ɾ���ľ�ĿID��
 * Output:      ��ʾɾ���Ƿ�ɹ�
 * Return:      0��ʾɾ��ʧ�ܣ�1��ʾɾ���ɹ�
 */
int Schedule_UI_Delete(int id){
	int rtn = 0;
	if (Schedule_Srv_DeleteByID(id))
	{	
		printf("\t\t\t�ݳ��ƻ�ɾ���ɹ���\n");
		rtn = 1;
	}
	else
	{
		printf("\t\t\t�ݳ��ƻ�ɾ��ʧ�ܣ�\n");
		printf("\t\t\t�밴�س������أ�");
	}
	getchar();
	return rtn;
}

/*
 * Function:    Schedule_UI_Query
 * Function ID:	TTMS_SCU_Schedule_UI_Qry
 * Description: ����ID�Ų�ѯ�ݳ��ƻ���Ϣ
 * Input:       �����ҵľ�ĿID��
 * Output:      ���ҵ��ľ�Ŀ��Ϣ
 * Return:      0��ʾδ�ҵ���1��ʾ�ҵ���
 */
int Schedule_UI_Query(int id){
	int rtn = 1;
    schedule_t  buf;
    
    if (Schedule_Srv_FetchByID( id, &buf)) {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t�p�פפפפפפפפפ�  IDΪ%2d���ݳ��ƻ�   �פפפפפפפפרp\n",buf.id);
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		printf("\n\n\n");
        rtn = 1;
        printf("�ƻ�ID: %d\n",buf.id);
        printf("��ĿID: %d\n",buf.play_id);
        printf("��ӳ��ID: %d\n",buf.studio_id);
        printf("�ݳ�����:%d��%d��%d��\n", buf.date.year, buf.date.month, buf.date.day);
        printf("�ݳ�ʱ��:%dʱ%d��%d��\n",buf.time.hour, buf.time.minute, buf.time.second);
        printf("��λ����:%d\n",buf.seat_count);
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
        printf("����س�������");
        while(getchar() != '\n');
    }
	else    
    {
        printf("\n\t\t\t���Ҳ������ݳ��ƻ���");
        sleep(1);
    }
    return rtn;
}

/*
 * Function:    Schedule_UI_ListByPlay
 * Function ID:	TTMS_SCU_Schedule_UI_ListByPlay
 * Description: ���б�ģʽ��ʾ������Ŀ���ݳ��ƻ���Ϣ
 * Input:       listΪ���ҵ����ݳ��ƻ���Ϣ�����ͷָ�룬playΪ��Ŀ��Ϣ��pagingΪ��ʾ��ҳ���ò���
 * Output:      ��
 * Return:      ���ز��ҵ��ļ�¼��Ŀ
 */
void Schedule_UI_ListByPlay(const play_t *play, schedule_list_t list, Pagination_t paging){
}

/*
 * Function:    Schedule_UI_MgtEntry
 * Function ID:	TTMS_SCU_Schedule_UI_MgtEnt
 * Description: �ݳ��ƻ�������棬�ݳ��ƻ����վ�Ŀ���й����Ծ�ĿID��Ϊ����
 * Input:       ��ؾ�ĿID��
 * Output:      �ݳ��ƻ���Ϣ
 * Return:      ��
 */
void Schedule_UI_MgtEntry(int play_id){
	int id;
	char choice;
	char ch;
	schedule_list_t head;          
	schedule_node_t *pos;          
	Pagination_t paging;         
	List_Init(head, schedule_node_t);        
	paging.offset = 0;       
	paging.pageSize = SCHEDULE_PAGE_SIZE;
	//��������
	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	do{
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t�p�פפפפפפפפפפ�   �ݳ��ƻ�����  �פפפפפפפפפרp\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		printf("\n\n\n");
		printf("\t\t\t[Y]��ӡ�ݳ��ƻ�\n");
		printf("\t\t\t[A]����ݳ��ƻ�\n");
		printf("\t\t\t[U]�޸��ݳ��ƻ�\n");
		printf("\t\t\t[D]ɾ���ݳ��ƻ�\n");
		printf("\t\t\t[Q]�����ݳ��ƻ�\n\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[P]��һҳ|[N]��һҳ|[R]����\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t��ѡ��:");
		fflush(stdin);
		scanf("%c",&choice);
		fflush(stdin);
		switch(choice)
		{
			case 'a':
			case 'A':
			 	//����ݳ��ƻ�
			 	if(Schedule_UI_Add(play_id))     //����ӳɹ����������һҳ��ʾ
				{
					paging.totalRecords = Schedule_Srv_FetchAll(head);
					Paging_Locate_LastPage(head, paging, schedule_node_t);
				}
				 break;
			case 'u':
			case 'U':
				//�޸��ݳ��ƻ�
				printf("\t\t\t���� ID:");
				while(scanf("%d",&id)!=1)
				{
					printf("\t\t\t������Ĳ�������\n");
					printf("\t\t\t���������룺");
					while((ch=getchar())!='\n')
					    continue; 
				}
				fflush(stdin);
				if (Schedule_UI_Delete(id)) {	//������������
					paging.totalRecords = Schedule_Srv_FetchAll(head);
					List_Paging(head, paging, schedule_node_t);
				}
				break;
			case 'd':
			case 'D':
				    //ɾ���ݳ��ƻ�
				printf("\t\t\t���� ID:");
				while(scanf("%d",&id)!=1)
				{
					printf("\t\t\t������Ĳ�������\n");
					printf("\t\t\t���������룺");
					while((ch=getchar())!='\n')
					    continue; 
				}
				fflush(stdin);
				if (Schedule_UI_Delete(id)) {	//������������
					paging.totalRecords = Schedule_Srv_FetchAll(head);
					List_Paging(head, paging, schedule_node_t);
				}	
				break;	
			case 'y':
			case 'Y':
				//��ӡ�ݳ��ƻ�
				Schedule_UI_ListAll();
				break;
			case 'q':
			case 'Q':
				printf("\t\t\t����Ҫ���ҵ�ID:");
				while(scanf("%d",&id)!=1)
				{
					printf("\t\t\t������Ĳ�������\n");
					printf("\t\t\t���������룺");
					while((ch=getchar())!='\n')
					    continue; 
				}
				fflush(stdin);
				Schedule_UI_Query(id);
				break;
			case 'p':
			case 'P':
				if (1 < Pageing_CurPage(paging))
				{
					Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
				}
				break;
			case 'n':
			case 'N':
				if (Pageing_TotalPages(paging) > Pageing_CurPage(paging))
				{
					Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
				}
				break;
		}
	}while(choice!='R' && choice!='r');
	//�ͷ�����ռ�
	List_Destroy(head, schedule_node_t);
}

