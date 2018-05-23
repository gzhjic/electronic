#include "tool.h"


Status InitQueue(SqQueue *Q)
/* 构造一个空循环队列 */
{
	Q->base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q->base) return(OVERFLOW);	//存储分配失败
	Q->front = Q->rear = 0;
	return OK;
}


int QueueLength(SqQueue Q)
/* 返回Q的元素个数，即队列长度 */
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}


Status EnQueue(SqQueue *Q, QElemType e)
/* 插入元素e为Q的新的队尾元素 */
{
	if ((Q->rear + 1) % MAXQSIZE == Q->front)
		return ERROR;		//队列满
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;
}


Status DeQueue(SqQueue *Q, QElemType *e)
/* 若队列非空，则删除Q的队头元素，用e返回其值
	若成功 返回OK，否则返回ERROR */
{
	if (Q->front == Q->rear)
		return ERROR;
	*e = Q->base[Q->front];
	Q->front = (Q->front + 1) % MAXQSIZE;
	return OK;
}