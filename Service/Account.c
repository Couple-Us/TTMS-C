#include "Account.h"
//#include "EntityKey.h"
#include "../Persistence/Account_Persist.h"
#include <string.h>
#include <stdlib.h>

extern account_t gl_CurUser;
extern char message[100]; 

//extern account_t gl_Admin;

//------------------------------------------------------------------------------------------------------
// Service
//����ϵͳ��ʼ���˺�admin
void Account_Srv_InitSys(){
//	account_t gl_Admin={999, USR_ADMIN, "admin","admin"};
//	if(Account_Perst_CheckAccFile())
//	    printf("�˺��ļ�������");
//	else
//	{
//		Account_Srv_Verify(gl_Admin->username,gl_Admin->password)
//        Account_Perst_Insert(&gl_Admin);
//	}
}
//��֤��¼�˺��Ƿ��Ѵ��ڣ����ڣ������¼�û���Ϣ��ȫ�ֱ���gl_CurUser��return 1������return 0
inline int Account_Srv_Verify(char usrName[], char pwd[]){
    if(!strcmp(usrName,gl_CurUser.username) && !strcmp(pwd,gl_CurUser.password))
	    return 1;
//	else
	    return 0;
}
//��֤�û����Ƿ���ڣ�����list�������ڣ����ض�Ӧ���ָ�룻���򣬷���null
account_node_t * Account_Srv_FindByUsrName(account_list_t list, char usrName[]) {

	return NULL ;
}
//���һ���û��˺ţ�ͨ������Account_Perst_Insert(data)����ʵ��
inline int Account_Srv_Add(const account_t *data){
	return 1;
}
//�޸�һ���û��˺ţ�ͨ������Account_Perst_Update(data)����ʵ��
inline int Account_Srv_Modify(const account_t *data){
	return 1;
}
//ɾ��һ���û��˺ţ�ͨ������Account_Perst_DeleteByID(usrID)����ʵ��
inline int Account_Srv_DeleteByID(int usrID){
	return 1;
}
//��ȡusrID��Ӧ���û��˺���Ϣ��ͨ������Account_Perst_SelectByID(usrID, buf)����ʵ��
inline int Account_Srv_FetchByID(int usrID, account_t *buf){
	return 1;
}
//��ȡusrName��Ӧ���û��˺���Ϣ��ͨ������Account_Perst_SelByName(usrName, buf)����ʵ��
inline int Account_Srv_FetchByName(char usrName[], account_t *buf){
	return 1;
}
//��ȡ�����û��˺���Ϣ�����浽list�����У�ͨ������Account_Perst_SelectAll(list)����ʵ��
inline int Account_Srv_FetchAll(account_list_t list){
	return 1;
}
//------------------------------------------------------------------------------------------------------
