// Persistence

#include "Account_Persist.h"
#include "../Service/account.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

extern account_t gl_CurUser;
extern account_t gl_Admin;
extern message;

//------------------------------------------------------------------------------------------------------
// Persistence
static const char ACCOUNT_DATA_FILE[] = "Account.dat";
static const char ACCOUNT_DATA_TEMP_FILE[] = "AccountTmp.dat";

//�ж��˺��ļ��Ƿ���ڣ�����1���ڣ�����0������
int Account_Perst_CheckAccFile() {
	FILE *fp;
	if((fp=fopen("Account.dat","rb"))==NULL)
	    return 0;
	return 1;
}
//�����û��������˺�,����ɹ� return 1������ return 0
int Account_Perst_SelByName(char usrName[], account_t *buf) {
	return 1;
}
//���˺�д���˺��ļ��У�����ʵ��д������ݿ���Ŀ
int Account_Perst_Insert(const account_t *data) {
	FILE *fp;
	fp=fopen("Account.dat","ab");
	fwrite(data,sizeof(data),1,fp);
//	strcpy(message,"...");
	return 1;
}
//���˺��ļ��в���������˺�ƥ����˺ţ��ҵ� return 1������ return 0�������и�����д
int Account_Perst_Update(const account_t * data) {
	return 1;
}
//���˺��ļ���ɾ�������idƥ����˺ţ�ɾ���ɹ� return 1������ return 0��
int Account_Perst_DeleteByID(int id) {
	return 1;
}
//���˺��ļ��в��������idƥ����˺ţ���ͨ��ָ��buf������ƥ��ɹ� return 1������ return 0��
int Account_Perst_SelectByID(int id, account_t *buf) {
	return 1;
}
//������ACCOUNT_DATA_FILE�ļ�����̬�����û��˺�list����,list Ϊ����ͷָ�룬����list����
int Account_Perst_SelectAll(account_list_t list) {
	return 1;
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/*
Consumer* read_list()
{
    FILE *fp;
    if ((fp = fopen("CONSUMER.dat", "rb")) == NULL)
    {
        printf("�޷���ȡ CONSUMER.dat\n");
        return NULL;
    }
    int sign;
    Consumer *s,*p,*head;
     
    head= (Consumer*)malloc(SIZE_C);
    if (head == NULL)
    {
        printf("��ȡʧ�ܣ��ڴ�ռ����벻�㣡\n");
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)
    {
        return NULL;
    }
    p = head;
    p->next = NULL;
    while (feof(fp))
    {
        s = (Consumer*)malloc(SIZE_C);
        //fread(s, SIZE_C, 1, fp);
                fread(s, sizeof(char), SIZE_C, fp);
        p->next = s;
        p = s;
        p->next = NULL;
    }
    fclose(fp);
    return head;
}//��ȡ�ļ�������
int save_consumer(Consumer *p)
{
    FILE *fp;
    Consumer *head;
    head = p;//pΪ�Ѿ������õ�����
    //if ((fp = fopen("CONSUMER.dat", "ab+")) == NULL)
        if ((fp = fopen("CONSUMER.dat", "wb")) == NULL)
    {
        printf("�޷��� CONSUMER.dat!\n");
        return -1;
    }
    while (p != NULL)
    {
        //fwrite(p, SIZE_C, 1, fp);
                fwrite(p, sizeof(char), SIZE_C, fp);
        p = p->next;
    }
    fclose(fp);
    return 1;
}//���������ļ�
*/
