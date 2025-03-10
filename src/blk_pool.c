#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "blk_pool.h"
#include "EmptyBlkManager/queue.h"
#include "UsedBlkManager/hashtable.h"

// 初始化 NvmCacheBlkPool
void initNvmBlkManager(NvmCacheBlkPool *manager, size_t hashTableSize) {
    initQueue(&manager->emptyBlocksQueue);
    manager->usedBlocksTable = createHashTable(hashTableSize);
}

// 构建 NVM 块
void buildNvmBlock(NvmCacheBlkPool *manager, uint64_t nvmBlock, uint64_t lba) {
    if (lba == UINT64_MAX) {  // LBA 为最大值时，构建为空块，使用队列管理
        enqueue(&manager->emptyBlocksQueue, nvmBlock);
    } else {  // 否则，构建为有效块，使用哈希表管理
        insert(manager->usedBlocksTable, lba, nvmBlock);
    }
}

// 获取空的 NVM 块号
int getEmptyBlock(NvmCacheBlkPool *manager, uint64_t *nvmBlock) {

    // 检查队列中是否有空块
    if (!isEmpty(&manager->emptyBlocksQueue)) {
        *nvmBlock = dequeue(&manager->emptyBlocksQueue);
        return 0;
    }

    // 如果队列中没有空块，从哈希表中返回下一个被分配的块号
    HashNode *node = next(manager->usedBlocksTable);
    if (node != NULL) {
        *nvmBlock = node->value;
        deleteKey(manager->usedBlocksTable, node->key);
        return 1;
    }

    *nvmBlock = UINT64_MAX;
    return 1;
}


uint64_t *searchNvmBlkOfLba(NvmCacheBlkPool *manager, uint64_t key){
    uint64_t *nvmBlk = search(manager->usedBlocksTable, key);
    return nvmBlk;
}

void destroyNvmBlkManager(NvmCacheBlkPool *manager){
    destructQueue(&manager->emptyBlocksQueue);
    destructHashTable(manager->usedBlocksTable);
}
