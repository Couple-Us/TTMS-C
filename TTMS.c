#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "View/Account_UI.h"

account_t gl_CurUser={9, USR_ANOMY, "admin","admin"};

char message[100];

int main()
{
	if(!SysLogin())
	{
		getchar();
		exit(0);
	}
	printf("\t\t\t%30c","");
	printf("��");Sleep(200);
	printf("��");Sleep(200);
	printf("��");Sleep(200);
	printf("¼");Sleep(200);
	printf("��");Sleep(200);
	printf("��");Sleep(300);
	printf("��");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	printf(".");Sleep(100);
	Main_Menu();
	return EXIT_SUCCESS;
}
