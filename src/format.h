#ifndef NVM_CACHE_FORMAT
#define NVM_CACHE_FORMAT

typedef struct NvmAccessor NvmAccessor;
typedef struct NvmCache NvmCache;

typedef struct NvmCacheFormatArgs {
    const char *lower_device_file;
    int queue_num;
    // TODO
} NvmCacheFormatArgs;

/***********************public API***********************/

int nvm_cache_is_formatted(int *res, NvmAccessor *accessor, const char *lower_device_file);
int nvm_cache_format(NvmAccessor *accessor, NvmCacheFormatArgs *arg);

/***********************public API***********************/

#endif