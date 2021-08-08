#include <cligen/cligen.h>
#include <clixon/clixon.h>
#include <cerrno>

#include "plugin_rpc.h"
#define IETF_TCP_NAMESPACE "urn:ietf:params:xml:ns:yang:ietf-tcp"

void RpcManager::register_rpc_callbacks(clicon_handle h) {

    //TODO: reset statistic rpc
    if (rpc_callback_register(h, rpc::reset_statistics, nullptr, IETF_TCP_NAMESPACE, "reset") < 0)
        throw std::runtime_error("'reset' rpc cannot be registered");
}

int rpc::reset_statistics(clicon_handle h, cxobj *requestXml, cbuf *xmlBuffer, void *arg, void *regarg) {

    // Example RPC Call
    //<rpc xmlns="urn:ietf:params:xml:ns:netconf:base:1.0" message-id="101">
    //    <action xmlns="urn:ietf:params:xml:ns:yang:1">
    //        <tcp xmlns="urn:ietf:params:xml:ns:yang:ietf-tcp">
    //            <statistics>
    //                <reset />
    //            </statistics>
    //        </tcp>
    //    </action>
    //</rpc>

    return 0;
}
