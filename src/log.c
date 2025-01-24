#include "log.h"
#include "core.h"

int log_manager_init(NvmLogManager *log_manager, NvmCache *cache) {
    // TODO
    return 0;
}

void log_manager_destruct(NvmLogManager *self) {
    // TODO
}

int log_manager_append_entry(NvmLogManager *self, LogEntry *entry) {
    // TODO
    return 0;
}

int log_manager_commit(NvmLogManager *self) {
    // TODO
    return 0;
}

int log_manager_recover(NvmLogManager *self) {
    // TODO
    return 0;
}

int log_entry_init(LogEntry **entry, LogEntryType type, void *content, u16 length) {
    // TODO
    return 0;
}

void log_entry_destrust(LogEntry *self) {
    // TODO
}