#include "tool.h"


Status InitQueue(SqQueue *Q)
/* ����һ����ѭ������ */
{
	Q->base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q->base) return(OVERFLOW);	//�洢����ʧ��
	Q->front = Q->rear = 0;
	return OK;
}


int QueueLength(SqQueue Q)
/* ����Q��Ԫ�ظ����������г��� */
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}


Status EnQueue(SqQueue *Q, QElemType e)
/* ����Ԫ��eΪQ���µĶ�βԪ�� */
{
	if ((Q->rear + 1) % MAXQSIZE == Q->front)
		return ERROR;		//������
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}


Status DeQueue(SqQueue *Q, QElemType *e)
/* �����зǿգ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ
	���ɹ� ����OK�����򷵻�ERROR */
{
	if (Q->front == Q->rear)
		return ERROR;
	*e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}