#ifndef _tool_h_
#define _tool_h_

#include <stdlib.h>

/* 状态码 */
typedef unsigned char Status;
#define ERROR       0
#define OK          1
#define OVERFLOW    2


/* 循环队列 */
#define MAXQSIZE 10	//最大队列长度

typedef unsigned char QElemType;

typedef struct {
	QElemType *base;	//初始化动态分配存储空间
	int front;			//头指针，若队列不空，指向队列头元素
	int rear;			//尾指针，若队列不空，指向队列尾元素的下一个位置
}SqQueue;


Status InitQueue(SqQueue *Q);
int QueueLength(SqQueue Q);
Status EnQueue(SqQueue *Q, QElemType e);
Status DeQueue(SqQueue *Q, QElemType *e);

#endif