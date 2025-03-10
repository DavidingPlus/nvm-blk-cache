#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "queue.h"

// 初始化队列
void initQueue(Queue *queue) {
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

// 判断队列是否为空
int isEmpty(Queue *queue) {
    return queue->size == 0;
}

// 从队列头插入数据
void enqueue(Queue *queue, uint64_t value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = queue->head;
    queue->head = newNode;
    if (queue->size == 0) {
        queue->tail = newNode;
    }
    queue->size++;
}

// 从队列尾删除并返回数据
uint64_t dequeue(Queue *queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Queue is empty!\n");
        return 0; // 可根据需要处理异常情况
    }
    
    Node *current = queue->head;
    Node *previous = NULL;
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    
    uint64_t value = current->data;
    
    // 删除尾部节点
    if (previous == NULL) { // 队列中只有一个节点
        queue->head = NULL;
        queue->tail = NULL;
    } else {
        previous->next = NULL;
        queue->tail = previous;
    }
    
    free(current);
    queue->size--;
    
    return value;
}

// 销毁队列，释放所有节点的内存
void destructQueue(Queue *queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
}

// 打印队列（用于调试）
void printQueue(Queue *queue) {
    Node *current = queue->head;
    while (current != NULL) {
        printf("%lu -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
