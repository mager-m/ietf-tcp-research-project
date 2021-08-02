#ifndef PLUGIN_TRANSACTION_H
#define PLUGIN_TRANSACTION_H

#include "plugin_options.h"

class TransactionManager {
public:
    static int trans_begin(clicon_handle h, transaction_data td);

    static int trans_validate(clicon_handle h, transaction_data td);

    static int trans_complete(clicon_handle h, transaction_data td);

    static int trans_commit(clicon_handle h, transaction_data data);

    static int trans_commit_done(clicon_handle h, transaction_data td);

    static int trans_revert(clicon_handle h, transaction_data td);

    static int trans_end(clicon_handle h, transaction_data td);

    static int trans_abort(clicon_handle h, transaction_data td);
};


#endif //PLUGIN_TRANSACTION_H
