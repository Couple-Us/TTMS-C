/*
 * salesanalysisPersist.c
 *	רҵ��ˮӡ�������� 
 *  Created on: 2015��6��21��
 *      Author: ���� 
 */

#include "../Persistence/EntityKey_Persist.h"
#include "../Service/play.h"
#include "../Service/Sale.h"
#include "../Service/salesanalysis.h"
#include "../Common/list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

//static const char PLAY_DATA_FILE[] = "play.dat";
static const char SALE_DATA_FILE[] = "sale.dat";
static const char SALESANALYSIS_DATA_FILE[] = "salesanalysis.dat";

//��һ��salesanalysis��¼��*data��д��salesanalysis.dat�ļ����ɹ�return 1������return 0
int Salesanalysis_Perst_Insert(const salesanalysis_t *data) {
//	salesanalysis_t *temp = NULL;
	FILE *output;
	if(0==data->play_id)
	{
		printf("�޼�¼����!\n");
		return 0;
	}
	if((output=fopen("salesanalysis.dat","ab"))==NULL) 
	{
		printf("���ļ�ʧ�ܣ���\n");
		return 0;
	}
	else
	{
//		fprintf(output,"%d %s %s %d %ld %ld %d %d-%d-%d %d-%d-%d \n",data->play_id,data->name,data->area,data->duration,data->totaltickets,data->sales,data->price,data->start_date.year,data->start_date.month,data->start_date.day,data->end_date.year,data->end_date.month,data->end_date.day);
		fwrite(data,sizeof(salesanalysis_t),1,output);
		printf("\nд��ɹ���\n");
		return 1;
	}

}

//������salesanalysis.dat�ļ��������۷�����salesanalysis������
int SalesAnalysis_Perst_SelectAll(salesanalysis_list_t list) {
	FILE *input;
	salesanalysis_t *temp;
	if((input=fopen("salesanalysis.dat","rb"))==NULL)
	{
		printf("���ļ�ʧ�ܣ�");
		return 0; 
	}
	else
	{
		/*¼��ѧ����Ϣ*/
		
		
		return 1;
	}

}

//������Sale.dat�ļ�����list��sale_list_t�� ������������list����
int Sale_Perst_SelectAll(sale_list_t list) {
	FILE *input;
	if((input=fopen("Sale.dat","rb"))==NULL)
	{
		printf("�ļ�������!\n");
		return 0;
	}
	return 1;
}

