#ifndef _tool_h_
#define _tool_h_

#include <stdlib.h>

/* ״̬�� */
typedef unsigned char Status;
#define ERROR       0
#define OK          1
#define OVERFLOW    2


/* ѭ������ */
#define MAXQSIZE 10	//�����г���

typedef unsigned char QElemType;

typedef struct {
	QElemType *base;	//��ʼ����̬����洢�ռ�
	int front;			//ͷָ�룬�����в��գ�ָ�����ͷԪ��
	int rear;			//βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ��
}SqQueue;


Status InitQueue(SqQueue *Q);
int QueueLength(SqQueue Q);
Status EnQueue(SqQueue *Q, QElemType e);
Status DeQueue(SqQueue *Q, QElemType *e);

#endif