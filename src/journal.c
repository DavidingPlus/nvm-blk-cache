#include "journal.h"
#include "core.h"

int journal_manager_init(NvmJournalManager *journal_manager, NvmCache *cache) {
    // TODO
    return 0;
}

void journal_manager_destruct(NvmJournalManager *self) {
    // TODO
}

int journal_manager_append_entry(NvmJournalManager *self, JournalEntry *entry) {
    // TODO
    return 0;
}

int journal_manager_commit(NvmJournalManager *self) {
    // TODO
    return 0;
}

int journal_manager_recover(NvmJournalManager *self) {
    // TODO
    return 0;
}

int journal_entry_init(JournalEntry **entry, JournalEntryType type, void *content, u16 length) {
    // TODO
    return 0;
}

void journal_entry_destrust(JournalEntry *self) {
    // TODO
}