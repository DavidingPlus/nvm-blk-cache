#include "nvm_accessor.h"

#include "nvm_addr_map_manager.h"
#include "defs.h"

#include <linux/io.h>
#include <linux/slab.h>

/***********************public API***********************/

NvmAccessor* nvm_accessor_init(NvmAddrMapManager* nvm_addr_map_manager){
    if (!nvm_addr_map_manager) {
        pr_err("nvm_addr_map_manager unvailed!");
        goto parameter_unvailed;
    }

    NvmAccessor* nvm_accessor = kmalloc(sizeof(nvm_accessor), GFP_KERNEL);
    if (!nvm_accessor) {
        pr_err("kmalloc Accessor fail!");
        goto kamlloc_fail;
    }

    nvm_accessor->nvm_addr_map_manager = nvm_addr_map_manager;
    return nvm_accessor;

kamlloc_fail:
parameter_unvailed:
    return NULL;
}

int global_nvm_accessor_init(NvmAddrMapManager* nvm_addr_map_manager){
    if (!nvm_addr_map_manager) {
        pr_err("nvm_addr_map_manager unvailed!");
        goto parameter_unvailed;
    }

    global_nvm_accessor.nvm_addr_map_manager = nvm_addr_map_manager;
    return 0;

parameter_unvailed:
    return EINVAL;
}

int accessor_destory(NvmAccessor* this){
    if(!this){
        pr_err("Accessor pointer unvaild!\n");
        return EINVAL;
    }
    kfree(this);
    return 0;
}

size_t nvm_accessor_write(NvmAccessor* this, void *buffer, size_t count, LbaType lba){
    return 0;
};

size_t nvm_accessor_read(NvmAccessor* this, void *buffer, size_t count, LbaType lba){
    return 0;
};

/***********************public API***********************/

/***********************private API***********************/

void* get_vaddr_by_paddr(NvmAccessor* this, phys_addr_t paddr){
    if(!this){
        pr_err("Accessor pointer unvaild!\n");
        return EINVAL;
    }

    void* vaddr = this->nvm_addr_map_manager
            ->phy_addr_map_virt_addr_func(this->nvm_addr_map_manager, paddr);
    return vaddr;
}

void* get_vaddr_by_lba(NvmAccessor* this, u64 lba){
    if(!this){
        pr_err("Accessor pointer unvaild!\n");
        return EINVAL;
    }

    phys_addr_t paddr = 
            lba * CACHE_BLOCK_SIZE + this->nvm_addr_map_manager->nvm_phy_start_addr;
    return get_vaddr_by_paddr(this, paddr);
}

/***********************private API***********************/
