#include "format.h"

#include "access.h"

#include <linux/module.h>


int nvm_cache_is_formatted(int *res, NvmAccessor *accessor, const char *lower_device_file)
{
    if (!res || !accessor || !lower_device_file)
    {
        pr_err("nvmcache: nvm_cache_is_formatted() invalid argument!\n");


        return -EINVAL;
    }

    *res = true;

    NvmObj obj = nvm_accessor_get_full_nvm_range(accessor);
    // NvmObj 不能直接访问，需要先进行映射。
    NvmVirtAddrRange virtAddr = nvm_accessor_start_access(accessor, &obj);

    if (!virtAddr.addr || (u64)0 == virtAddr.len) *res = false;

    // TODO 可能还需验证 NVM 头部的一些标识信息，依赖 NVM 管理器。

    nvm_accessor_end_access(accessor, &obj);


    return 0;
}

int nvm_cache_format(NvmAccessor *accessor, NvmCacheFormatArgs *arg)
{
    // TODO NVM 物理布局的格式化，依赖 NVM 管理器的接口。
    return 0;
}
