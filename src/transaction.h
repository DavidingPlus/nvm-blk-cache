#ifndef NVM_CACHE_TRANSACTION
#define NVM_CACHE_TRANSACTION

#include "defs.h"
typedef struct NvmCache NvmCache;
typedef struct NvmJournalManager NvmJournalManager;

typedef struct NvmTransactionManager {
    NvmJournalManager *journal_mgr;
    // TODO
} NvmTransactionManager;

typedef struct NvmTransaction {
    TxnId id;
    NvmTransactionManager *txn_mgr;
    // TODO
} NvmTransaction;

/***********************public API***********************/

int nvm_txn_manager_init(NvmTransactionManager *txn_mgr, NvmCache *cache);
void nvm_txn_manager_destruct(NvmTransactionManager *self);

// 对当前NVM状态进行一次检查点
// 如果是redo日志，除了正在进行的事务，其它所有事务的日志都要应用完成，再写检查点日志
// 如果是undo日志，可直接写入检查点，附带当前正在进行的事务
int nvm_txn_do_checkpoint(NvmTransactionManager *self);

// 初始化时调用，对所有日志进行故障恢复
int nvm_txn_recover(NvmTransactionManager *self);

// 启动一个新事务，将事务上下文初始化到new_txn中
int nvm_txn_start(NvmTransaction *new_txn, NvmTransactionManager *txn_mgr, ResourceId resource_id);
void nvm_txn_destruct(NvmTransaction *self);

// 事务提交，提交后self只能被析构，不能再写日志
int nvm_txn_commit(NvmTransaction *self);

// 事务回滚，回滚后self只能被析构，不能再写日志
int nvm_txn_abort(NvmTransaction *self);

/***********************public API***********************/

#endif