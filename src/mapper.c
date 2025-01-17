#include "mapper.h"
#include "core.h"

int cache_mapper_init(NvmCacheMapper *mapper, NvmCache *cache) {
    // TODO 
    return 0;
}

void cache_mapper_destruct(NvmCacheMapper *self) {
    // TODO
}

int cache_mapper_get(NvmCacheMapper *self, LbaType lba, NvmCacheBlkId *id) {
    // TODO
    return 0;
}

int cache_mapper_set(NvmCacheMapper *self, LbaType lba, NvmCacheBlkId id, NvmTransaction *txn) {
    // TODO
    return 0;
}

int cache_mapper_remove(NvmCacheMapper *self, LbaType lba, NvmTransaction *txn) {
    // TODO
    return 0;
}