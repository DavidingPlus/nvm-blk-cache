#include "format.h"

#include "access.h"
#include "defs.h"

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

    // TODO 还需验证 NVM 头部的一些标识信息。

    nvm_accessor_end_access(accessor, &obj);


    return 0;
}

// TODO NvmCacheFormatArgs 参数暂时不知道有什么作用。
int nvm_cache_format(NvmAccessor *accessor, NvmCacheFormatArgs *arg)
{
    NvmObj obj = nvm_accessor_get_full_nvm_range(accessor);
    NvmVirtAddrRange virtAddr = nvm_accessor_start_access(accessor, &obj);

    // 在头部的 lba 数组中写 8 字节的全 f 取默认值。
    LbaType lbaDefault = 0xffffffffffffffff;
    u64 size = virtAddr.len / (8 + 4 * 1024);
    for (u64 i = 0; i < size; ++i) memcpy((char *)virtAddr.addr + i * 8, &lbaDefault, 8);


    return 0;
}
