#ifndef NVM_CACHE_LOWER_DEV
#define NVM_CACHE_LOWER_DEV

#include <linux/types.h>

#include "defs.h"

// 提供底层块设备的同步I/O接口。在 NvmCache 构造和析构，以及和需要读写底层块设备时使用它即可。

typedef struct block_device block_device;

typedef struct NvmCacheLowerDev {
    const char *dev_name;
    block_device *bd;
} NvmCacheLowerDev;

typedef struct LowerDevIoReq {
    LbaType sector;  // 大小单位512字节
    u64 sector_num;
    void *buffer;
    NvmCacheIoDir dir;
} LowerDevIoReq;

/***********************public API***********************/

int lower_dev_init(NvmCacheLowerDev *dev, const char *dev_name);
void lower_dev_destruct(NvmCacheLowerDev *self);
u64 lower_dev_get_sector_num(NvmCacheLowerDev *self);

// 底层设备同步I/O接口
// req中的buffer必须指向dram缓冲区，不能是NVM上的空间，因为bio依赖page
int lower_dev_io(NvmCacheLowerDev *self, LowerDevIoReq *req);

/***********************public API***********************/

#endif