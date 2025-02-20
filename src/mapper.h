#ifndef NVM_CACHE_MAPPER
#define NVM_CACHE_MAPPER

#include "defs.h"

// 缓存的底层块设备扇区地址形式是逻辑块地址（LBA），NVM 上需要持久化当前缓存的 LBA 逻辑块地址和缓存块号的映射关系，NvmCacheMapper 管理 NVM 上这些数据和元数据。

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