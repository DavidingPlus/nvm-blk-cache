#include "transaction.h"

#include "core.h"

int nvm_txn_manager_init(NvmTransactionManager *tx_mgr, NvmCache *cache) {
    // TODO
    return 0;
}

void nvm_txn_manager_destruct(NvmTransactionManager *self) {
    // TODO
}

int nvm_txn_start(NvmTransaction *new_txn, NvmTransactionManager *txn_mgr, ResourceId resource_id) {
    // TODO
    return 0;
}

void nvm_txn_destruct(NvmTransaction *self) {
    // TODO
}

// 事务提交，提交后self只能被析构，不能再写日志
int nvm_txn_commit(NvmTransaction *self) {
    // TODO
    return 0;
}

// 事务回滚，回滚后self只能被析构，不能再写日志
int nvm_txn_abort(NvmTransaction *self) {
    // TODO
    return 0;
}