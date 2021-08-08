#include <cligen/cligen.h>
#include <clixon/clixon.h>

#include "plugin_lifecycle.h"

int LifecycleManager::plugin_start(clicon_handle h) {
    return 0;
}

int LifecycleManager::plugin_exit(clicon_handle h) {
    return 0;
}

int LifecycleManager::plugin_daemon(clicon_handle h) {
    return 0;
}
