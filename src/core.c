#include "core.h"
#include "access.h"

int nvm_cache_init(NvmCache *cache, NvmAccessor *accessor) {
    // TODO
    return 0;
}

void nvm_cache_destruct(NvmCache *self) {
    // TODO    
}

block_device *nvm_cache_get_lower_device(NvmCache *self) {
    // TODO
    return NULL;
}