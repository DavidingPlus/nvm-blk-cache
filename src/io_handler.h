#ifndef NVM_CACHE_IO_HANDLER
#define NVM_CACHE_IO_HANDLER

#include "defs.h"

typedef struct NvmCache NvmCache;

// 封装 I/O 请求的元数据。
typedef struct NvmCacheIoReq {
    LbaType lba;        // 逻辑块地址 LBA。
    u64 lba_num;        // 连续处理的扇区数量。
    void *buffer;       // 用户空间数据缓冲区的内核虚拟地址指针。
    NvmCacheIoDir dir;  // 操作方向（读或写）。

    // 收到IO请求的队列的下标，范围[0, hw_queue_count)
    // 如果设计为资源换并发，可用于获取每队列独占资源
    ResourceId resource_id;
} NvmCacheIoReq;

/***********************public API***********************/

// I/O请求处理总入口
// 当此块设备收到上层的写请求时，分配一个缓存块向其中写入数据，建立 LBA 与缓存块的映射关系，如果 NVM 上缓存大小不足，需要进行缓存块回写到底层块设备等操作。收到上层读请求时，根据映射关系检查目标块是否在 NVM 上有缓存，如果有将缓存块拷贝到上层缓冲区，否则向底层块设备发起读请求读出目标块。
int nvm_cache_handle_io(NvmCache *cache, NvmCacheIoReq *req);

/***********************public API***********************/

#endif