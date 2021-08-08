#ifndef PLUGIN_RPC_H
#define PLUGIN_RPC_H

#include <stdexcept>

using namespace std;

class RpcManager {
public:

    /*! Register callback for routing rpc calls
    * @param[in]  h     Clicon handle
    */
    static void register_rpc_callbacks(clicon_handle h);

};

namespace rpc {

    /*! RPC Reset Statistics
    * @param[in] h              Clicon handle
    * @param[in] *requestXml    Request: <rpc><xn></rpc>
    * @param[in] *xmlBuffer     Reply eg <rpc-reply>...
    * @param[in] *arg           client_entry
    * @param[in] *regarg        Argument given at register
    */
    int reset_statistics(clicon_handle h, cxobj *requestXml, cbuf *xmlBuffer, void *arg, void *regarg);
}

#endif //PLUGIN_RPC_H
