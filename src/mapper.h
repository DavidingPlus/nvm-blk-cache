#ifndef NVM_CACHE_MAPPER
#define NVM_CACHE_MAPPER

#include "defs.h"

typedef struct NvmCache NvmCache;
typedef struct NvmTransaction NvmTransaction;

// 简单实现：以扇区为单位管理缓存，可以确保IO不会访问到单个缓存块的部分范围，方便管理
typedef struct NvmCacheMapper {
    // TODO
    // 可以用Dram上的哈希表+NVM上的log实现(参考NVM文件系统方案)。
    // 这种数据结构在NVM上通用，可以封装起来单独实现，这里变成更上层的包装
} NvmCacheMapper;

/***********************public API***********************/

int cache_mapper_init(NvmCacheMapper *mapper, NvmCache *cache);
void cache_mapper_destruct(NvmCacheMapper *self);

int cache_mapper_get(NvmCacheMapper *self, LbaType lba, NvmCacheBlkId *id);
int cache_mapper_set(NvmCacheMapper *self, LbaType lba, NvmCacheBlkId id, NvmTransaction *txn);
int cache_mapper_remove(NvmCacheMapper *self, LbaType lba, NvmTransaction *txn);

/***********************public API***********************/

#endif