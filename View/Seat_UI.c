/*
 *  Seat_UI.c
 *
 *  Created on: 2015��5��23��
 *  Author: lc
 */
#include "Seat_UI.h"

#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Common/list.h"
#include <stdio.h>
#include <string.h>

extern char message[100];

//����״̬���ض�Ӧ��ʾ״̬����
inline char Seat_UI_Status2Char(seat_status_t status) {

	char statusChar;
	switch (status) {
		case SEAT_GOOD:		//����λ
			statusChar = '#';
			break;
		case SEAT_BROKEN:	//�𻵵���λ
			statusChar = '~';
			break;
		case SEAT_NONE:
		default:
			statusChar = ' ';
			break;
	}
	return statusChar;
}

//����״̬���ŷ�����λ״̬
inline seat_status_t Seat_UI_Char2Status(char statusChar) {
	seat_status_t status;
	switch (statusChar) {
	case '#':		//����λ
		status = SEAT_GOOD;
		break;
	case '~':	//�𻵵���λ
		status = SEAT_BROKEN;
		break;
	default:
		status = SEAT_NONE;
		break;
	}
	return status;
}

void Seat_UI_MgtEntry(int roomID) {
	int i, j;
	char choice;
	int seatCount;
	int enterflag; 
	int changedCount = 0;
	studio_t studioRec;
	if (!Studio_Srv_FetchByID(roomID, &studioRec)) {  //��ö�Ӧid��ӳ������Ϣ
	    strcpy(message,"\n\t\t\t���ݳ����������ڣ�");
		getchar();
		return;
	}
	seat_list_t list;
	seat_node_t *p;
	List_Init(list, seat_node_t);
	//ѡ���ӳ����������λ
	seatCount = Seat_Srv_FetchByRoomID(list, roomID);
	if (!seatCount) {		//����ӳ����û��������λ�����Զ�������λ
		seatCount = Seat_Srv_RoomInit(list, roomID, studioRec.rowsCount,
				studioRec.colsCount);
		//�޸��ݳ��������λ����
		studioRec.seatsCount = seatCount;
		Studio_Srv_Modify(&studioRec);
	}
	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t�p�פפפפפפפפפפ�   �ݳ��� ID: %2d �פפפפפפפפפרp\n",roomID);
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		printf("\t\t\t===============================================================\n");
		printf("\n\t\t\t�ܹ���%d�С�\n",studioRec.rowsCount);
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
		//��ʾ����
		for (i = 1; i <= studioRec.rowsCount; i++) {
			j = 1;
		    enterflag=1;
			printf("\t\t\t��%2d:%c", i, ' ');
			List_ForEach(list,p)
			{
				if (p->data.row == i) {
					while (p->data.column != j) {
						printf("%3c", ' ');
						j++;
					}
					printf("%-2c", Seat_UI_Status2Char(p->data.status));
					if(enterflag%29==0)
					    printf("\n\t\t\t      ");
					enterflag++;
					j++;
				}
			}
			printf("\n");
		}
		printf("\n\t\t\t[A]������λ|[D]ɾ����λ|[U]������λ|[R]����");
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t����������ѡ��");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
		switch (choice) {
		case 'a':
		case 'A':
			changedCount = Seat_UI_Add(list, roomID, studioRec.rowsCount,
					studioRec.colsCount);
			if (changedCount > 0) {
				seatCount += changedCount;
				//�޸��ݳ��������λ����
				studioRec.seatsCount = seatCount;
				Studio_Srv_Modify(&studioRec);
			}
			break;
		case 'd':
		case 'D':
			changedCount = Seat_UI_Delete(list, studioRec.rowsCount,
					studioRec.colsCount);
			if (changedCount > 0) {
				seatCount -= changedCount;
				//�޸��ݳ��������λ����
				studioRec.seatsCount = seatCount;
				Studio_Srv_Modify(&studioRec);
			}
			break;
		case 'u':
		case 'U':
			Seat_UI_Modify(list, studioRec.rowsCount, studioRec.colsCount);
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//�ͷ�����ռ�
	List_Destroy(list, seat_node_t);
}

int Seat_UI_Add(seat_list_t list, int roomID, int row, int column) {  //����һ����λ
	seat_t rec;
	seat_node_t *p;
	int newRecCount = 0;
	char choice;
	char ch;
	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t�p�פפפפפפפפפפפ�  �������λ �פפפפפפפפפפרp\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		printf("\n\n"); 
		do {
			printf("\n\t\t\t��λ������Ӧ�ó��� %2d ���� ��λ������Ӧ�ó��� %2d��\n",row, column);
			printf("\n\t\t\t��λ������");
			while(scanf("%d", &(rec.row))!=1)
			{
				printf("\t\t\t������Ĳ�������\n");
				printf("\t\t\t���������룺");
				while((ch=getchar())!='\n')
				    continue; 
			}
			printf("\t\t\t��λ������");
			while(scanf("%d", &(rec.column))!=1)
			{
				printf("\t\t\t������Ĳ�������\n");
				printf("\t\t\t���������룺");
				while((ch=getchar())!='\n')
				    continue; 
			}
			fflush(stdin);
		} while (rec.row > row || rec.column > column);
		p = Seat_Srv_FindByRowCol(list, rec.row, rec.column);
		if (p) {						//����������к�����Ӧ����λ�Ѵ��ڣ����ܲ���
			strcpy(message,"\t\t\t����λ�Ѿ����ڣ�\n");
			break;
		}
		rec.id = EntKey_Srv_CompNewKey("Seat");		//������λid
		rec.roomID = roomID;
		rec.status = SEAT_GOOD;    //���������λ��״̬Ĭ��Ϊ����λ
		printf("\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		if (Seat_Srv_Add(&rec)) {
			newRecCount++;
			printf("\t\t\t����λ����ɹ���\n");
			p = (seat_node_t*) malloc(sizeof(seat_node_t));
			p->data = rec;
			Seat_Srv_AddToSoftedList(list, p); //������������λ�������list
		} else
			printf("\t\t\t����λ����ʧ�ܣ�\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[A]���������λ|[R]����\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t����������ѡ��");
		fflush(stdin);
		scanf("%c", &choice);
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

int Seat_UI_Modify(seat_list_t list, int row, int column) {
	int rtn = 0;
	int newrow, newcolumn;
	char choice;
	char ch;
	seat_node_t *p;
    system("cls");
	printf("\n\n\n");
	printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
	printf("\t\t\t�p�פפפפפפפפפפפ�   ������λ  �פפפפפפפפפפרp\n");
	printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
	printf("\n\n\n"); 
	do {
		do {				//���µ���λ������Ϣ���ܳ�����ӳ����������
			printf("\n"); 
			printf("\t\t\t��λ������Ӧ�ó��� %2d ���� ��λ������Ӧ�ó��� %2d��\n",row, column);
			printf("\t\t\t��λ������");
			scanf("%d", &newrow);
			printf("\t\t\t��λ������");
			scanf("%d", &newcolumn);
		} while (newrow > row || newcolumn > column);

		p = Seat_Srv_FindByRowCol(list, newrow, newcolumn);
		if (p) {
			printf("\t\t\t��λ[%d,%d]״̬Ϊ��[%c]��\n", newrow, newcolumn,Seat_UI_Status2Char(p->data.status));
			printf("\t\t\t�������µ�״̬(#/~/ )��"); 
			fflush(stdin);
			p->data.status = Seat_UI_Char2Status(getchar());
			fflush(stdin);
			printf("\n\n\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
			if (Seat_Srv_Modify(&(p->data))) {
				rtn = 1;
				printf("\n\t\t\t��λ���³ɹ���\n");
			} else
				printf("\n\t\t\t��λ����ʧ�ܣ�!\n");
		} else
			printf("\n\t\t\t����λ�������ڣ�\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[U]���¸�����λ|[R]����\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t����������ѡ��");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
	} while ('u' == choice || 'U' == choice);
	return rtn;
}

int Seat_UI_Delete(seat_list_t list, int row, int column) {

	int delSeatCount = 0;
	int newrow, newcolumn;
	seat_node_t *p;
	char choice;
	char ch;
	int i=1;

	do {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = = �[\n");
		printf("\t\t\t�p�פפפפפפפפפפפ�   ɾ����λ  �פפפפפפפפפפרp\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = ==�a\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t����ɾ����%-2d����λ\n",i); 
		do {
			fflush(stdin);
			printf("\n\t\t\t��λ������Ӧ�ó��� %2d ���� ��λ������Ӧ�ó��� %2d��\n",row, column);
			printf("\t\t\t��λ������");
			while(scanf("%d", &(newrow))!=1)
			{
				printf("\t\t\t������Ĳ�������\n");
				printf("\t\t\t���������룺");
				while((ch=getchar())!='\n')
				    continue; 
			}
			printf("\t\t\t��λ������");
			while(scanf("%d", &(newcolumn))!=1)
			{
				printf("\t\t\t������Ĳ�������\n");
				printf("\t\t\t���������룺");
				while((ch=getchar())!='\n')
				    continue; 
			}
			fflush(stdin);
		} while (newrow > row || newcolumn > column);

		p = Seat_Srv_FindByRowCol(list, newrow, newcolumn);
		if (p)
		{
			printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
			if (Seat_Srv_DeleteByID(p->data.id))
			{
				printf("\n\t\t\t��λɾ���ɹ���\n");
				delSeatCount++;
				List_FreeNode(p);	//�ͷŽ����λ���p
			}
		}
		else
		{
			printf("\t\t\t����λ�������ڣ�\n");
		}
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[D]ɾ��������λ|[R]����\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\t\t\t����������ѡ��");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
		i++	;
	} while ('d' == choice || 'D' == choice);
	return delSeatCount;
}

