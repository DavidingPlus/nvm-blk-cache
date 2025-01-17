#include "access.h"

int nvm_accessor_init(NvmAccessor *accessor, const char *phy_ranges, unsigned long virt_start,
                      unsigned long virt_size) {
    // TODO
    return 0;
}

void nvm_accessor_destruct(NvmAccessor *self) {
    // TODO
}

NvmVirtAddrRange nvm_accessor_start_access(NvmAccessor *self, NvmObj *obj) {
    NvmVirtAddrRange ret = {};

    // TODO: 增加访问引用计数，如果首次访问，则建立页表映射

    return ret;
}

void nvm_accessor_end_access(NvmAccessor *self, NvmObj *obj) {
    // TODO: 减少访问引用计数，如果为0，可以取消页表映射，也可以根据策略延迟取消
}

NvmObj nvm_accessor_get_full_nvm_range(NvmAccessor *self) {
    NvmObj ret = {};
    // TODO
    return ret;
}