#include "accessor.h"

#include "nvm_addr_map_manager.h"
#include "defs.h"

#include <linux/io.h>
#include <linux/slab.h>

/***********************public API***********************/

Accessor* accessor_init(NvmAddrMapManager* nvm_addr_map_manager){
    if (!nvm_addr_map_manager) {
        pr_err("nvm_addr_map_manager unvailed!");
        goto parameter_unvailed;
    }

    Accessor* accessor = kmalloc(sizeof(Accessor), GFP_KERNEL);
    if (!accessor) {
        pr_err("kmalloc Accessor fail!");
        goto kamlloc_fail;
    }

    accessor->nvm_addr_map_manager = nvm_addr_map_manager;
    return accessor;

kamlloc_fail:
parameter_unvailed:
    return NULL;
}

int accessor_destory(Accessor* this){
    if(!this){
        pr_err("Accessor pointer unvaild!\n");
        return EINVAL;
    }
    kfree(this);
    return 0;
}

void* get_vaddr_by_paddr(Accessor* this, phys_addr_t paddr){
    void* vaddr = this->nvm_addr_map_manager
            ->phy_addr_map_virt_addr_func(this->nvm_addr_map_manager, paddr);
    return vaddr;
}

void* get_vaddr_by_lba(Accessor* this, u64 lba){
    phys_addr_t paddr = 
            lba * CACHE_BLOCK_SIZE + this->nvm_addr_map_manager->nvm_phy_start_addr;
    return get_vaddr_by_paddr(this, paddr);
}

/***********************public API***********************/
