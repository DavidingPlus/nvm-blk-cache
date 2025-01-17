#ifndef NVM_CACHE_JOURNAL
#define NVM_CACHE_JOURNAL

#include <linux/types.h>
#include "defs.h"

typedef struct NvmCache NvmCache;

// WAL日志管理器，管理NVM上的日志区。日志区可以使用nvm上的循环队列实现。
typedef struct NvmJournalManager {
    // TODO
} NvmJournalManager;

typedef enum JournalEntryType {
    tx_begin,
    tx_commit,
    tx_abort,
    checkpoint,
    // TODO：各类NVM上进行修改的物理日志条目，如有需要也可讨论并设计逻辑日志
} JournalEntryType;

// 每一条日志条目的定义，结构体大小由type决定
typedef struct JournalEntry {
    TxnId id;
    JournalEntryType type;
    u16 length;  // 变长数组长度
    char entry[];
} JournalEntry;

/***********************public API***********************/

int journal_manager_init(NvmJournalManager *journal_manager, NvmCache *cache);
void journal_manager_destruct(NvmJournalManager *self);

// 写入一个日志条目，不一定要写到NVM中，也可暂时保存到内存缓冲区
int journal_manager_append_entry(NvmJournalManager *self, JournalEntry *entry);

// 确保所有日志条目写入NVM，且队列尾指针原子更新到写入后的尾部
int journal_manager_commit(NvmJournalManager *self);

// 故障恢复后，根据日志设计进行redo/undo恢复，并将self置为可正常写入日志的状态
// 应该由transaction模块间接调用，因为目前不确定WAL日志的实现方式
// （统一持久化资源与WAL日志区 or 每队列持久化资源与WAL日志区 + 中心持久化资源与中心WAL日志区？）
int journal_manager_recover(NvmJournalManager *self);

// 分配并构造journalentry, 地址保存到*entry中
int journal_entry_init(JournalEntry **entry, JournalEntryType type, void *content, u16 length);
void journal_entry_destrust(JournalEntry *self);

// TODO：实现各类journalentry的构造函数，内部构造完content后，再调用journal_entry_init完成构造

/***********************public API***********************/

#endif