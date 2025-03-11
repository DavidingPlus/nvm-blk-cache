#ifndef ACCESSOR
#define ACCESSOR

#include "nvm_addr_map_manager.h"

typedef struct Accessor
{
    NvmAddrMapManager *nvm_addr_map_manager;
    // TODO 内存保护：需要访问的时候建立地址映射
} Accessor;

/***********************public API***********************/

Accessor *accessor_init(NvmAddrMapManager *nvm_addr_map_manager);

int accessor_destory(Accessor *this);

void *get_vaddr_by_paddr(Accessor *this, phys_addr_t paddr);

// 一个lab对应一个扇区，一个扇区假定是512字节
void *get_vaddr_by_lba(Accessor *this, u64 lba);

// TODO read/write()

/***********************public API***********************/

// private API 写在 .c，防止暴露给用户

#endif