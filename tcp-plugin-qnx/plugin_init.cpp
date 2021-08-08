#include "plugin_options.h"
#include "plugin_state.h"
#include "plugin_rpc.h"
#include "plugin_lifecycle.h"
#include "plugin_transaction.h"

// Backend plugin initialization
clixon_plugin_api *clixon_plugin_init(clicon_handle h) {
    clicon_debug(1, "%s backend", __FUNCTION__);

    static clixon_plugin_api api;
    strcpy(api.ca_name, "tcp");
    api.ca_init = clixon_plugin_init;
    api.ca_start = LifecycleManager::plugin_start;
    api.ca_exit = LifecycleManager::plugin_exit;
    api.u.cau_backend.cb_daemon = LifecycleManager::plugin_daemon;
    api.u.cau_backend.cb_reset = StatedataManager::reset_system_state;
    api.u.cau_backend.cb_statedata = StatedataManager::query_statedata;
    api.u.cau_backend.cb_trans_begin = TransactionManager::trans_begin;
    api.u.cau_backend.cb_trans_validate = TransactionManager::trans_validate;
    api.u.cau_backend.cb_trans_complete = TransactionManager::trans_complete;
    api.u.cau_backend.cb_trans_commit = TransactionManager::trans_commit;
    api.u.cau_backend.cb_trans_commit_done = TransactionManager::trans_commit_done;
    api.u.cau_backend.cb_trans_revert = TransactionManager::trans_revert;
    api.u.cau_backend.cb_trans_end = TransactionManager::trans_end;
    api.u.cau_backend.cb_trans_abort = TransactionManager::trans_abort;

    try {
        Settings::read_cli_args(h);
        RpcManager::register_rpc_callbacks(h);
    } catch (exception &e) {
        clicon_err(OE_FATAL, errno, "Initialization error %s", e.what());
    }

    return &api;
}
