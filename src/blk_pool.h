#ifndef NVM_BLK_MANAGER_H
#define NVM_BLK_MANAGER_H

#include <stdint.h>
#include "EmptyBlkManager/queue.h"
#include "UsedBlkManager/hashtable.h"

// NVM 块管理结构体
typedef struct NvmCacheBlkPool {
    Queue emptyBlocksQueue;  // 用于管理空块的队列
    HashTable *usedBlocksTable;  // 用于管理有效块的哈希表
} NvmCacheBlkPool;

// 初始化 NvmCacheBlkPool
void initNvmBlkManager(NvmCacheBlkPool *manager, size_t hashTableSize);

// 构建 NVM 块
void buildNvmBlock(NvmCacheBlkPool *manager, uint64_t nvmBlock, uint64_t lba);

// 获取空的 NVM 块号
// 如果返回值为0，则返回的是空nvm块
// 如果返回值为1，且nvmBlock号有效，则返回的是已分配的块，并且该块已不再被blk_pool管理
// 如果返回值为1，且nvmBlock号为UINT64_MAX，则该执行逻辑出了bug
int getEmptyBlock(NvmCacheBlkPool *manager, uint64_t *nvmBlock);

uint64_t *searchNvmBlkOfLba(NvmCacheBlkPool *manager, uint64_t key);

void destroyNvmBlkManager(NvmCacheBlkPool *manager);

#endif // NVM_BLK_MANAGER_H
