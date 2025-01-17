#ifndef NVM_CACHE_ACCESS
#define NVM_CACHE_ACCESS

#include <linux/compiler.h>
#include <linux/types.h>

/*
 * 保存此次运行时Nvm的物理地址范围列表，和映射到的连续的虚拟地址范围
 * 使用类似引用计数的方法维护当前NvmObj的访问次数，只要当前任一NvmObj还活跃，就维持页表映射
 */
typedef struct NvmAccessor {
    int reserved;  // 占位，测试用，不能让NvmAccessor大小为0，开发时删掉
    // TODO
} NvmAccessor;

/*
 * NvmObj: 代表NVM上的一个物理地址范围，称为一个“对象”
 * 在Nvm上的任何数据结构中的指针都应该使用偏移量，而不是物理地址/虚拟地址，因为下次启动这些地址可能变化

 * 任何返回指向Nvm上对象的指针的函数，都返回NvmObj(或其子类)，调用者通过NvmObj的start_access方法映射当前虚拟地址便于访问
 * 目的是在API层面保证访问Nvm之前都进行了页表映射，杜绝非法访问
 * 如果这种API不好用，可以设计新的NvmObj方法以直接获得其映射的虚拟地址，页表映射单独管理
*/
typedef struct NvmObj {
    NvmAccessor *accessor;
    u64 phy_offset;
    u64 len;
    // TODO
} NvmObj;

/* 可安全访问的虚拟地址范围 */
typedef struct NvmVirtAddrRange {
    void *addr;
    u64 len;
} NvmVirtAddrRange;

NvmVirtAddrRange nvm_accessor_start_access(NvmAccessor *self, NvmObj *obj);
void nvm_accessor_end_access(NvmAccessor *self, NvmObj *obj);

/***********************public API***********************/

// 构造NvmAccessor对象。phy_ranges格式参考对应的模块参数说明
int nvm_accessor_init(NvmAccessor *accessor, const char *phy_ranges, unsigned long virt_start, unsigned long virt_size);

// 析构NvmAccessor对象
void nvm_accessor_destruct(NvmAccessor *self);

// 获得代表整个NVM物理区域范围的NvmObj对象，可用于格式化
NvmObj nvm_accessor_get_full_nvm_range(NvmAccessor *self);

static __always_inline NvmObj nvmobj_new(NvmAccessor *accessor, u64 phy_offset, u64 len) {
    NvmObj ret = {.accessor = accessor, .phy_offset = phy_offset, .len = len};
    return ret;
}

static __always_inline NvmVirtAddrRange nvmobj_start_access(NvmObj *self) {
    NvmVirtAddrRange ret;
    ret = nvm_accessor_start_access(self->accessor, self);
    return ret;
}

static __always_inline void nvmobj_end_access(NvmObj *self) { nvm_accessor_end_access(self->accessor, self); }

/***********************public API***********************/

#endif