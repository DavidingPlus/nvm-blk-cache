#include "nvm_manager.h"

#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/io.h>


/***********************private API***********************/

void* phy_addr_map_virt_addr(NvmManager *this, phys_addr_t nvm_phy_addr){
    long offset_of_paddr_and_vaddr = (unsigned long)this->nvm_virt_start_addr - this->nvm_phy_start_addr;
    return (void *) (nvm_phy_addr += offset_of_paddr_and_vaddr);
}

/***********************private API***********************/

/***********************public API***********************/

NvmManager* nvm_addr_map_manager_init(
        phys_addr_t nvm_phy_start_addr, unsigned long nvm_phy_length){
    
    NvmManager *nvm_manager;
    phys_addr_t aligned_nvm_phy_start_addr, aligned_nvm_phy_end_addr;
    void *nvm_virt_start_addr;
    unsigned long aligned_nvm_phy_length, nvm_virt_length;;

    aligned_nvm_phy_start_addr = nvm_phy_start_addr;
    aligned_nvm_phy_length     = nvm_phy_length;
    // 4K对齐 // ! 不能对物理地址进行裁剪
    // aligned_nvm_phy_start_addr = (nvm_phy_start_addr + PAGE_ALIGN_4K - 1) & PAGE_ALIGN_MASK_4K;
    // aligned_nvm_phy_end_addr   = (nvm_phy_start_addr + nvm_phy_length) & PAGE_ALIGN_MASK_4K;

    // if(aligned_nvm_phy_start_addr >= aligned_nvm_phy_end_addr){
    //     pr_err("aligned physical range wrong!\n");
    //     goto aligned_fail;
    // }
    // aligned_nvm_phy_length = aligned_nvm_phy_end_addr - aligned_nvm_phy_start_addr;

    // 建立映射 //? 映射函数是否需要抽象出来？
    if (!request_mem_region(aligned_nvm_phy_start_addr, aligned_nvm_phy_length, "memremap")) {
        pr_err("request_mem_region fail!\n");
        goto request_mem_region_fail;
    }
    nvm_virt_start_addr = memremap(aligned_nvm_phy_start_addr, aligned_nvm_phy_length, MEMREMAP_WB);
    if (!nvm_virt_start_addr) {
        pr_err("memremap fail!\n");
        goto memremap_fail;
    }

    // 申请管理器
    nvm_manager = kmalloc(sizeof(NvmManager), GFP_KERNEL);
    if(nvm_manager == NULL){
        pr_err("kmalloc NvmAddrMapManager fail!\n");
        goto kamlloc_fail;
    }
    nvm_virt_length = aligned_nvm_phy_length;
    nvm_manager->nvm_phy_start_addr          = aligned_nvm_phy_start_addr;
    nvm_manager->nvm_phy_length              = aligned_nvm_phy_length;
    nvm_manager->nvm_virt_start_addr         = nvm_virt_start_addr;
    nvm_manager->nvm_virt_length             = aligned_nvm_phy_length;
    nvm_manager->phy_addr_map_virt_addr_func = phy_addr_map_virt_addr;

    return nvm_manager;

kamlloc_fail:
    memunmap(&aligned_nvm_phy_start_addr);   // ? 为什么不用提供内存长度
memremap_fail:
    release_region(aligned_nvm_phy_start_addr, aligned_nvm_phy_length);
request_mem_region_fail:
aligned_fail:
    return NULL;
}

int nvm_addr_map_manager_destory(NvmManager* this){
    if(!this){
        pr_err("NvmAddrMapManager pointer unvaild!\n");
        return EINVAL;
    }

    memunmap(&this->nvm_phy_start_addr);
    release_region(this->nvm_phy_start_addr, this->nvm_phy_length);
    kfree(this);
    return 0;
}

void* nvm_phy_addr_map_virt_addr(NvmManager *this, phys_addr_t phy_addr){
    void* nvm_virt_addr;

    if(this->nvm_phy_start_addr > phy_addr ||
       this->nvm_phy_start_addr + this->nvm_phy_length < phy_addr){
        pr_info("nvm_phy_addr out of the mapped phyaddr!\n");
        return NULL;
    }
    
    nvm_virt_addr = this->phy_addr_map_virt_addr_func(this, phy_addr);
    if(!nvm_virt_addr){
        pr_info("phy_addr_map_virt_addr fail!\n");
        return NULL;
    }

    return nvm_virt_addr;
}

/***********************public API***********************/