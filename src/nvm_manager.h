#ifndef NVM_MANAGER
#define NVM_MANAGER

#include <linux/types.h>

#define PAGE_ALIGN_4K       (1 << 12)
#define PAGE_ALIGN_MASK_4K  (~(PAGE_ALIGN_4K - 1))

/* //TODO 处理多段映射关系
    struct NvmAddrMapEntry{
        phys_addr_t nvm_phy_start_addr;
        unsigned long nvm_phy_length;
        void *nvm_virt_start_addr;
        unsigned long nvm_virt_length;
        void* (*phy_addr_map_virt_addr)(phys_addr_t);
    }
    struct NvmAddrMapManager{
        *NvmAddrMapEntry nvm_addr_map_list;
    }
*/

typedef struct NvmManager{
    phys_addr_t nvm_phy_start_addr;
    unsigned long nvm_phy_length;
    void *nvm_virt_start_addr;
    unsigned long nvm_virt_length;
    void* (*phy_addr_map_virt_addr_func)(struct NvmManager*, phys_addr_t);
}NvmManager;

/***********************private API***********************/

// void* phy_addr_map_virt_addr(NvmAddrMapManager* this, phys_addr_t nvm_phy_addr);
// void* phy_addr_map_virt_addr_in_vmalloc(NvmAddrMapManager *this, phys_addr_t nvm_phy_addr);

/***********************private API***********************/

/***********************public API***********************/

// 地址映射管理构造 // ? 单例模式？
NvmManager* nvm_addr_map_manager_init(
        phys_addr_t nvm_phy_start_addr, unsigned long nvm_phy_length);

int nvm_addr_map_manager_destory(NvmManager* this);

// 提供给访问器accessor的接口
void* nvm_phy_addr_map_virt_addr(NvmManager* this, phys_addr_t phy_addr);

/***********************public API***********************/

#endif