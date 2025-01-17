#include "blk_pool.h"

int blk_pool_init(NvmCacheBlkPool *blk_pool, NvmCache *cache) {
    // TODO
    return 0;
}

void blk_pool_destruct(NvmCacheBlkPool *self) {
    // TODO
}

int blk_pool_alloc(NvmCacheBlkPool *self, NvmCacheBlkId *new_id, NvmTransaction *txn) {
    // TODO
    return 0;
}

int blk_pool_free(NvmCacheBlkPool *self, NvmCacheBlkId id, NvmTransaction *txn) {
    // TODO
    return 0;
}

int blk_pool_evict(NvmCacheBlkPool *self, NvmCacheBlkId *evict_id, NvmTransaction *txn) {
    // TODO
    return 0;
}

int blk_pool_flush(NvmCacheBlkPool *self, NvmTransaction *txn) {
    // TODO
    return 0;
}