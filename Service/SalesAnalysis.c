/*
 * salesanalysis.c
 *	ˮӡ���� 
 *  Created on: 2015��6��21��
 *      Author: ���� 
 */
#include <string.h>
#include <stdio.h>
#include "SalesAnalysis.h"
#include "../Persistence/Sale_Persist.h"
#include "../Persistence/SalesAnalysis_Persist.h"
#include "Sale.h"
#include "Ticket.h"
#include "Play.h"
#include "Schedule.h"
#include "../Common/list.h"

//����Ա��usrID�ڸ���ʱ����������۶�������۶�
inline int Salesanalysis_Srv_CompSaleVal(int usrID, user_date_t stDate, user_date_t endDate){
	int amount=0;
	/*����sale_list_t��������saleList*/
	sale_list_t saleList;
	/*����sale_node_tָ�����pSale*/
	sale_node_t *pSale;
	/*��saleList������г�ʼ��*/
	List_Init(saleList,sale_node_t);
	/*����id����ƥ���������Ϣ������saleList����*/
	Sale_Perst_SelectByUsrID(saleList, usrID,stDate,endDate); 
	List_ForEach(saleList,pSale)
	{
		/*�ۼ����۶�*/ 
		amount+=pSale->data.value;
	}
	/*ɾ�������ͷ��ڴ�*/
	List_Destroy(saleList,sale_node_t); 
	return amount; 
}

//��Ͼ�ĿPlay.dat,ͳ���������ݣ��������۷���salesanalysis_list_t list��������list������
int Salesanalysis_Srv_StaticSale(salesanalysis_list_t list)
{
	int count = 0;
	assert(NULL!=list);
	play_list_t playList,pos;
	salesanalysis_node_t *newNode;
	int sold,total;
	//�����Ŀ�б�
	List_Free(list,salesanalysis_node_t);
	/*�����ʼ��*/ 
	List_Init(playList,play_node_t);
	/*����������������Ϣ*/ 
	Play_Srv_FetchAll(playList);
	/*ѭ������*/ 
	List_ForEach(playList,pos)
	{
		printf("\t\t\t��Ŀ ID:%s\n",pos->data.name);
		newNode = (salesanalysis_node_t*)malloc(sizeof(salesanalysis_node_t));
		if(!newNode)
		{
			printf("\t\t\t�ڴ����ʧ��!!\n");
			break;
		}
		newNode->data.play_id = pos->data.id;
		strcpy(newNode->data.name,pos->data.name);
		strcpy(newNode->data.area,pos->data.area);
		newNode->data.duration = pos->data.duration;
		newNode->data.start_date = pos->data.start_date;
		newNode->data.end_date	= pos->data.end_date;
		newNode->data.price = pos->data.price;
		newNode->data.sales = Schedule_Srv_StatRevByPlay(pos->data.id,&sold,&total);
		newNode->data.totaltickets = sold;
		List_AddTail(list,newNode);
		count++;
	}
	/*ɾ�������ͷ��ڴ�*/ 
	List_Destroy(playList,play_node_t);
	printf("\t\t\t��������ɣ�\n");
	/*���ؽ�����*/ 
	return count;
}

//�Ծ�Ժ��ӰƱ������
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list){
}


