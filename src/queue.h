#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

// 节点结构
typedef struct Node {
    uint64_t data;
    struct Node *next;
} Node;

// 队列结构
typedef struct Queue {
    Node *head;       // 队列头
    Node *tail;       // 队列尾
    uint64_t size;    // 队列中节点的数量
} Queue;

// 初始化队列
void initQueue(Queue *queue);

// 判断队列是否为空
int isEmpty(Queue *queue);

// 从队列头插入数据
void enqueue(Queue *queue, uint64_t value);

// 从队列尾删除并返回数据
uint64_t dequeue(Queue *queue);

// 销毁队列，释放所有节点的内存
void destructQueue(Queue *queue);

// 打印队列（用于调试）
void printQueue(Queue *queue);

#endif /* QUEUE_H */
