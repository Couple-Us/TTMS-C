#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include <conio.h>

#include "Account_UI.h"
#include "../Service/Account.h"
//#include "../Service/EntityKey.h"
#include "../Common/list.h"
#include "Account_UI.h"
#define WRONGTIMES 3

account_node_t *pMain=NULL;

extern account_t gl_CurUser;
//extern account_t gl_Admin;
extern char message[100];

int menuflag=1;
int iCount;
int loginWrongTimes=0;

int SysLogin() {
	account_node_t *p;
    
	char username[20];
	char password[20];
	char ch;
	int i=0;
	Account_Srv_InitSys();
	fflush(stdin);
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t�p�פפפפפפפפ�  X��ӰԺƱ�����ϵͳ  �פפפפפפפפרp\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
	if(loginWrongTimes==0)
	{
    	strcpy(message,"\n\t\t\t�������ε�½���ᣬ���ȵ�¼��");
	    puts(message);
	}
	else
	{
		puts(message);
	}
    printf("\n\t\t\t\t%-35s","�������û�����");
    scanf("%s",username);
	printf("\t\t\t\t%-35s","���룺");
    while((ch=getch())!='\r')
    {
        if(ch!=8)//���ǻس���¼��
        {
            password[i]=ch;
            putchar('*');//�������*��
            i++;
        }
        else
        {
            putchar('\b');//������ɾ��һ��������ͨ������س��� /b���س�һ��
            putchar(' ');//����ʾ�ո���Ѹղŵ�*����ס��
            putchar('\b');//Ȼ���� �س�һ��ȴ�¼�롣
            i--;
        }
    }
    password[i]='\0';
    printf("\n\n");
    printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
    if((!Account_Srv_Verify(username,password)))
//    while(!Account_Srv_Verify(username,password))
    {
    	loginWrongTimes++;
    	if(loginWrongTimes==WRONGTIMES)
    	{
    		printf("\n\t\t\t�Բ��������3����,��������Ȩ��¼��ϵͳ\n");
			printf("\n\t\t\t�����κ���������ϵ����Ա,���س����˳�......\n");
			getchar();
			return 0;
		}
		sprintf(message,"\n\t\t\t���ĵ�¼��Ϣ�������������룡������%d�λ��ᡣ",WRONGTIMES-loginWrongTimes);
	    if(SysLogin()==0)
		    return 0;
	}
	loginWrongTimes=0;
	return 1;
}

//����ϵͳ�û�������ں�������ʾ�û��˺Ź���˵�
void Account_UI_MgtEntry() {
	char ch;
	int choice;
	char username[20];
	char password[20];
	int i=4;
	system("cls");
	fflush(stdin);
	printf("\n\n\n");
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t�p�פפפפפפפפפפ�   �û��˺Ź���  �פפפפפפפפפרp\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
	if(menuflag==1)
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
	    menuflag++;
	}
	else
	    puts(message);
    printf("\n");
    printf("\t\t\t[0] ��¼�����˺�\n");
    printf("\t\t\t[1] ���һ���˺�\n");
    printf("\t\t\t[2] �޸�һ���˺�\n");
    printf("\t\t\t[3] ɾ��һ���˺�\n");
    printf("\t\t\t[4] ���һ���˺�\n");
    printf("\t\t\t[5] ����ָ���˺�\n");
    printf("\t\t\t[6] ��ʾ�����˺�\n");
    printf("\t\t\t[7] �˺�¼���ļ�\n");
    printf("\t\t\t[8] �޸ĵ�ǰ�˺�����\n");
    printf("\t\t\t[9] ����\n");
	printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
    printf("\n\t\t\t����������ѡ��");
    if(scanf("%d",&choice)!=1)
    {
    	while((ch=getchar())!='\n')
    	    continue;
    	strcpy(message,"\n\t\t\t������Ĳ������֡�");
    	Account_UI_MgtEntry();
	}
    switch(choice)
    {
    	case 0:
    		printf("\t\t\t��¼�˺��з��գ�ȷ����¼��(y/����)");
    		fflush(stdin);
    		if((ch=getchar()!='y'))
    		{
    			menuflag--;
    			break;
			}
    		fflush(stdin);
    		pMain=Creat_Node();
    		strcpy(message,"\n\t\t\t¼���˺ųɹ���");
    		break;
    	case 1:
    		if(pMain==NULL)
    		    strcpy(message,"\n\t\t\tû����ӵ��˺š�");
            else
    		    Account_UI_Add(pMain);
    		break;
    	case 2:
    		if(pMain==NULL)
    		    strcpy(message,"\n\t\t\tû�п����޸ĵ��˺š�");
            else
            {
                printf("\n\t\t\t��������Ҫ�޸ĵ��˺�����");
				scanf("%s",username);
				if(Account_UI_Modify(pMain,username))
				    printf("\n\t\t\t�޸ĳɹ���");
				else
				    printf("\n\t\t\t�޸�ʧ�ܡ�"); 
			}
    		break;
    	case 3:
    		if(pMain==NULL)
    		    strcpy(message,"\n\t\t\tû�п���ɾ�����˺š�");
            else
            {
            	printf("\n\t\t\tɾ���ʺ���е����գ�");
                printf("\n\t\t\t��������Ҫɾ�����˺�����");
				scanf("%s",username);
				Account_UI_Delete(pMain,username);
			}
    		break;
    	case 4:
    		if(pMain==NULL)
    		    strcpy(message,"\n\t\t\t����û�����ɡ�");
    		else
    		    Account_UI_Add(pMain);
		    break;
		case 5:
			if(pMain==NULL)
			    strcpy(message,"\n\t\t\t����û�����ɡ�");
    		else
    		{
				printf("\n\t\t\t��������Ҫ��ѯ���˺�����");
				scanf("%s",username); 
				if(Account_UI_Query(pMain,username))
				    strcpy(message,"\n\t\t\t���˺��Ѿ�ע�ᡣ");
				else
				    strcpy(message,"\n\t\t\t���˺���δע�ᡣ");
			}
			break;
		case 6:
//    		if(pMain==NULL)
//    		    strcpy(message,"\n\t\t\tû����¼����˻���"); 
//            else
//			    Print_Node(pMain);
    		strcpy(message,"\n\t\t\t�������ע���˺Ź�����δ��ͨ��"); 
    		break;
    	case 7:
    		Account_Perst_CheckAccFile();
    		strcpy(message,"\n\t\t\t�˺�¼���ļ�������δ��ͨ��"); 
    		break;
    	case 8:
    		strcpy(message,"\n\t\t\t�޸ĵ�ǰ�˺�������δ��ͨ��");
    		break;
    	case 9:
    		Main_Menu();
		    break;
    	default:
    		strcpy(message,"\n\t\t\t������ 0-9������"); 
    		while(ch!='\n')
    		    ch=getchar();
			break;
	}
	Account_UI_MgtEntry();
}

account_node_t *Creat_Node()
{
	int n,i;
	char ch;
    account_node_t *p,*h,*s;
    iCount=0;
    system("cls");
    if((h=(account_node_t *)malloc(sizeof(account_node_t)))==NULL)
    {
    	strcpy(message,"\n\t\t\t\t\t\t�Բ��𣬳����޷������ڴ�ռ�");
        return NULL;        
    }
    h->data.username[0]='\0';
    h->prev=NULL;
    h->next=NULL;
    p=h;
    printf("\n\n\n");
    printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t�p�פפפפפפפפפפ�   ��¼�����ʺ�  �פפפפפפפפפרp\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
    printf("\n\t\t\t׼��¼����˺�������Ϣ������");
    if(scanf("%d",&n)!=1)
    {
    	while((ch=getchar())!='\n')
    	    continue;
    	strcpy(message,"\n\t\t\t������Ĳ������֡�");
    	Account_UI_MgtEntry();
	}
    for(i=0;i<n;i++)
    {
        if((s=(account_node_t *)malloc(sizeof(account_node_t)))==NULL)
        {
	        strcpy(message,"\n\t\t\t\t\t\t�Բ��𣬳����޷������ڴ�ռ�");
            return NULL;
        }
        p->next=s;
        printf("\n\t\t\t����¼��� %d ����\n",i+1);
        printf("\t\t\t\t%-35s","�˺ţ�");
        scanf("%s",s->data.username);
        printf("\t\t\t\t%-35s","���룺");
        scanf("%s",s->data.password);
        printf("\t\t\t\t%-35s","[1]��Ʊ\\[2]����\\[����]����");
		while(scanf("%d",&s->data.type)!=1)
	    {
	    	while((ch=getchar())!='\n')
	    	    continue;
	    	printf("\n\t\t\t%-35s\n","����������������������");
	    	printf("\t\t\t\t%-35s","[1]��Ʊ\\[2]����\\[����]����");
		}
		if(s->data.type!=0 && s->data.type!=1 && s->data.type!=2)
		    s->data.type=9;
//		Account_Srv_Add(&s);
		s->prev=p;
	    s->next=NULL;
	    p=s;
	    iCount++;
    }
    h->prev=NULL;
    return(h);
}

int Account_UI_Add(account_list_t list ) {
	account_node_t *pNew,*pTemp=list;
	int choice;
	char ch; 
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t�p�פפפפפפפפפפ�   ���һ���ʺ�  �פפפפפפפפפרp\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
	do
	{
		pNew=(account_node_t *)malloc(sizeof(account_node_t));
		printf("\n\t\t\t¼����Ҫ��ӵ����˺�������Ϣ��\n");
		printf("\t\t\t\t%-35s","�˺ţ�");
		scanf("%s",pNew->data.username);
		printf("\t\t\t\t%-35s","���룺");
		scanf("%s",pNew->data.password);
		printf("\t\t\t\t%-35s","����(\\1��Ʊ\\2����\\9����)��");
		scanf("%d",&pNew->data.type);
		while(pTemp->next)
			pTemp=pTemp->next;
		pTemp->next=pNew;
		pNew->prev=pTemp;
		pNew->next=NULL;
		printf("\n\t\t\t�Ƿ�������([1]����/[����]�˳�)��");
		while(scanf("%d",&choice)!=1)
	    {
	    	while((ch=getchar())!='\n')
	    	    continue;
	    	printf("\n\t\t\t%-35s\n","������Ĳ������֣�����������");
	    	printf("\t\t\t\t%-35s","����(\\1��Ʊ\\2����\\9����)��");
		}
	}while(choice==1);
	strcpy(message,"\n\t\t\t��ӳɹ���");
	iCount++;
	return 1;
}
// 2
int Account_UI_Modify(account_list_t list ,char usrName[]) {
	account_node_t *pTemp=list;
	char temppsw[20];
	char confirmpsw[20];
	char ch;
	int i=0;
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t�p�פפפפפפפפפפ�   �޸�һ���ʺ�  �פפפפפפפפפרp\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
	do
	{
		if(!strcmp(pTemp->data.username,usrName))
		    break;
		pTemp=pTemp->next;
	}while(pTemp);
    printf("\n\t\t\t���˻���ϢΪ��\n");
    printf("\t\t\t\t�˺ţ�%30s \n",pTemp->data.username);
    printf("\t\t\t\t���룺%30s \n",pTemp->data.password);
    printf("\t\t\t\t����%30d \n",pTemp->data.type);
	printf("\n\t\t\t%-30s","�������µ����룺");
	while((ch=getch())!='\r')
    {
        if(ch!=8)//���ǻس���¼��
        {
            temppsw[i]=ch;
            putchar('*');//�������*��
            i++;
        }
        else
        {
            putchar('\b');//������ɾ��һ��������ͨ������س��� /b���س�һ��
            putchar(' ');//����ʾ�ո���Ѹղŵ�*����ס��
            putchar('\b');//Ȼ���� �س�һ��ȴ�¼�롣
            i--;
        }
    }
    temppsw[i]='\0';
	printf("\n\t\t\t%-30s","��ȷ���������룺");
	while((ch=getch())!='\r')
    {
        if(ch!=8)//���ǻس���¼��
        {
            confirmpsw[i]=ch;
            putchar('*');//�������*��
            i++;
        }
        else
        {
            putchar('\b');//������ɾ��һ��������ͨ������س��� /b���س�һ��
            putchar(' ');//����ʾ�ո���Ѹղŵ�*����ס��
            putchar('\b');//Ȼ���� �س�һ��ȴ�¼�롣
            i--;
        }
    }
    confirmpsw[i]='\0';
	if(strcmp(temppsw,confirmpsw))
	{ 
	    strcpy(message,"\n\t\t\t�������벻һ�¡�");
	    return 0;
	}
	strcpy(pTemp->data.password,temppsw);
	strcpy(message,"\n\t\t\t�޸ĳɹ���");
	return 1;
}

// 3 �����û��˺���ɾ��һ���Ѿ����ڵ��û��˺���Ϣ���������������û��˺�������ʾ������Ϣ
int Account_UI_Delete(account_list_t list ,char usrName[]) {
	account_node_t *pTemp,*pFree;
	int flag=0;
	system("cls");
	getchar();
	printf("\t\t\t��Ҫɾ�����˺��ǣ�%s\n",usrName);
	pTemp=list;
	do
	{
		if(!strcmp(pTemp->data.username,usrName))
		{
		    flag=1;    
			break;
		}
		pTemp=pTemp->next;
	}while(pTemp);
	if(flag!=1)
	{
	    strcpy(message,"\n\t\t\t���˻�������");
	    return 0;
	}
    else
    {
    	pFree=pTemp;
    	if(pTemp->prev->prev==NULL && pTemp->next==NULL)
    	{
    	    pMain=NULL;
		}
    	else if(pTemp->prev==NULL && pTemp->next!=NULL)
    	{
    		pTemp=pTemp->next;
    		pTemp->prev=NULL;
		}
    	else if(pTemp->prev!=NULL && pTemp->next!=NULL)
    	{
    		pTemp->prev->next=pTemp->next;
		    pTemp->next->prev=pTemp->prev;
		}
	    else if(pTemp->prev!=NULL && pTemp->next==NULL)
	    {
	    	pTemp=pTemp->prev;
	    	pTemp->next=NULL;
		}
		free(pFree);
	    strcpy(message,"\n\t\t\tɾ���ɹ���");
	    iCount--;
		return 1;
	}
}
// 5 �����û��˺������Ҹ��û��˺��Ƿ���ڣ����ڷ���1�����򷵻�0������ʾ������Ϣ
int Account_UI_Query(account_list_t  list ,char usrName[]) {
	account_node_t *pTemp=list;
	system("cls");
	printf("\n\n\n"); 
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t�p�פפפפפפפפפפ�   ��ѯһ���ʺ�  �פפפפפפפפפרp\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
	while(pTemp)
	{
		if(strcmp(pTemp->data.username,usrName))
		    break; 
		pTemp=pTemp->next;
	}
	return 1;
}

account_node_t Print_Node(const account_node_t *userinfo)
{
	int pageSize,i;
	Pagination_t paging;
	account_node_t *p;
	char choice,ch;
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t�p�פפפפפפפפפפ�   ��ʾ�����ʺ�  �פפפפפפפפפרp\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
	printf("\t\t\t������ÿҳ��ʾ�ĸ�����");
	while(scanf("%d",&pageSize)!=1)
	{
	    while((ch=getchar())!='\n')
	        continue;
	    printf("\t\t\t������Ĳ������֣����������롣\n");
	    printf("\t\t\t����ÿҳ��ʾ�ĸ�����");
	}
	//��ʼ����ҳ������
	paging.offset = 0;
	paging.pageSize = pageSize;
	paging.totalRecords = iCount;
	//��λ����һҳ
	Paging_Locate_FirstPage(userinfo, paging);
	system("cls");
	do {
		printf("\n\n\n");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t�p�פפפפפפפפפפ�   ��ʾ�����ʺ�  �פפפפפפפפפרp\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		printf("\t\t\tÿҳ��ʾ�ĸ����ǣ�%d\n",pageSize);
		printf("\n\t\t\t%s\t\t%s\t\t%s\n", "�˺�", "����","�˺�����");
		Paging_ViewPage_ForEach(userinfo, paging, account_node_t, p, i);
		{
			printf("\t\t\t%s\t\t%s", p->data.username, p->data.password);
		}
	    switch(userinfo->data.type)
		{
			case USR_ANOMY:
				printf("\t\t%s\n","�����û�");
			    break; 
			case USR_CLERK: 
			    printf("\t\t%s\n","����Ա");
				break;
			case USR_MANG:
			    printf("\t\t%s\n","����");
			    break;
			case USR_ADMIN:
			    printf("\t\t%s\n","ϵͳ����Ա");
				break;
			default:
				printf("\t\t\terror��");
		}
		printf("\t\t\t--�ܹ� %2d ����¼ --------- ��ǰ�� %2d/%2d --\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		printf("\t\t\t[F]��һҳ|[P]��һҳ|[N]��һҳ|[L]���һҳ|[E]�˳�\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t����������ѡ��:");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
		switch (choice) {
		case 'f':
		case 'F':
			Paging_Locate_FirstPage(userinfo, paging)
			;
			break;
		case 'p':
		case 'P':
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(userinfo, paging, -1, account_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(userinfo, paging, 1, account_node_t);
			}
			break;
		case 'l':
		case 'L':
			Paging_Locate_LastPage(userinfo, paging, account_node_t)
			;
			break;
		}
		system("cls");
	} while (choice != 'e' && choice != 'E');
	menuflag--;
} 
