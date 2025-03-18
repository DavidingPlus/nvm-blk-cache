#ifndef NVM_ACCESSOR
#define NVM_ACCESSOR

#include "nvm_addr_map_manager.h"
#include "defs.h"

typedef struct NvmAccessor{
    NvmAddrMapManager* nvm_addr_map_manager;
    // TODO 内存保护：需要访问的时候建立地址映射
}NvmAccessor;

extern NvmAccessor global_nvm_accessor;

/***********************public API***********************/

NvmAccessor* nvm_accessor_init(NvmAddrMapManager* nvm_addr_map_manager);

int global_nvm_accessor_init(NvmAddrMapManager* nvm_addr_map_manager);

int nvm_accessor_destory(NvmAccessor* this);

size_t nvm_accessor_write(NvmAccessor* this, void *buffer, size_t count, LbaType lba);

size_t nvm_accessor_read(NvmAccessor* this, void *buffer, size_t count, LbaType lba);

/***********************public API***********************/

// void* get_vaddr_by_paddr(NvmAccessor* this, phys_addr_t paddr);

// 一个lab对应一个扇区，一个扇区假定是512字节
// void* get_vaddr_by_lba(NvmAccessor* this, u64 lba);


#endif