#include <syslog.h>

#include <cligen/cligen.h>
#include <clixon/clixon.h>
#include <clixon/clixon_backend.h>

#include "plugin_transaction.h"

int TransactionManager::trans_begin(clicon_handle h, transaction_data td) {
    auto *settings = Settings::getInstance();
    if (settings->cliOptions->enableTransactionLogging)
        transaction_log(h, td, LOG_NOTICE, __FUNCTION__);
    return 0;
}

int TransactionManager::trans_validate(clicon_handle h, transaction_data td) {
    auto *settings = Settings::getInstance();
    if (settings->cliOptions->enableTransactionLogging)
        transaction_log(h, td, LOG_NOTICE, __FUNCTION__);
    return 0;
}

int TransactionManager::trans_complete(clicon_handle h, transaction_data td) {
    auto *settings = Settings::getInstance();
    if (settings->cliOptions->enableTransactionLogging)
        transaction_log(h, td, LOG_NOTICE, __FUNCTION__);
    return 0;
}


int TransactionManager::trans_commit(clicon_handle h, transaction_data data) {
    auto *settings = Settings::getInstance();
    if (settings->cliOptions->enableTransactionLogging)
        transaction_log(h, data, LOG_NOTICE, __FUNCTION__);
    return 0;
}

int TransactionManager::trans_commit_done(clicon_handle h, transaction_data td) {
    auto *settings = Settings::getInstance();

    if (settings->cliOptions->enableTransactionLogging)
        transaction_log(h, td, LOG_NOTICE, __FUNCTION__);
    return 0;
}

int TransactionManager::trans_revert(clicon_handle h, transaction_data td) {
    auto *settings = Settings::getInstance();

    if (settings->cliOptions->enableTransactionLogging)
        transaction_log(h, td, LOG_NOTICE, __FUNCTION__);
    return 0;
}

int TransactionManager::trans_end(clicon_handle h, transaction_data td) {
    auto *settings = Settings::getInstance();

    if (settings->cliOptions->enableTransactionLogging)
        transaction_log(h, td, LOG_NOTICE, __FUNCTION__);
    return 0;
}

int TransactionManager::trans_abort(clicon_handle h, transaction_data td) {
    auto *settings = Settings::getInstance();

    if (settings->cliOptions->enableTransactionLogging)
        transaction_log(h, td, LOG_NOTICE, __FUNCTION__);
    return 0;
}

