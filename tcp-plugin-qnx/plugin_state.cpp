#include <cerrno>

#include <cligen/cligen.h>
#include <clixon/clixon.h>
#include <stdexcept>
#include <regex>

#include "plugin_state.h"
#include "utility_tcp.h"


int StatedataManager::reset_system_state(clicon_handle h, const char *db) {
    return 0;
}

int StatedataManager::query_statedata(clicon_handle h, cvec *nsc, char *xpath, cxobj *xstate) {
    if (query_statedate_from_machine(h, nsc, xpath, xstate) < 0)
        return -1;

    return 0;
}


int StatedataManager::query_statedate_from_machine(clicon_handle h, cvec *nsc, char *xpath, cxobj *xstate) {
	cbuf *cbuf = nullptr;
	TCPStats *tcpStats = nullptr;
	std::list<TCPConnection *> *tcpConnections = nullptr;

    try {
        // TODO: Xpath filter support -> <filter type="xpath" xmlns:t="urn:ietf:params:xml:ns:yang:ietf-tcp" select="/t:tcp/t:connections" />
    	tcpStats = TCPStatisticsManager::readStatistics();
    	tcpConnections = TCPConnectionManager::readConnections();

        cbuf = cbuf_new();
        cprintf(cbuf, "<tcp xmlns=\"urn:ietf:params:xml:ns:yang:ietf-tcp\">");

        //connections
        cprintf(cbuf, "<connections>");
        for (auto connection : *tcpConnections) {
            cprintf(cbuf, "<connection>");
            cprintf(cbuf, "<local-address>%s</local-address>", connection->localAddress->ipAddress.c_str());
            cprintf(cbuf, "<remote-address>%s</remote-address>", connection->remoteAddress->ipAddress.c_str());
            cprintf(cbuf, "<local-port>%s</local-port>", connection->localAddress->port.c_str());
            cprintf(cbuf, "<remote-port>%s</remote-port>", connection->remoteAddress->port.c_str());
            cprintf(cbuf, "</connection>");
        }
        cprintf(cbuf, "</connections>");

        // statistics
        cprintf(cbuf, "<statistics>");
        cprintf(cbuf, "<active-opens>%s</active-opens>", tcpStats->activeOpens.c_str());
        cprintf(cbuf, "<passive-opens>%s</passive-opens>", tcpStats->passiveOpens.c_str());
        cprintf(cbuf, "<attempt-fails>%s</attempt-fails>", tcpStats->attemptFails.c_str());
        cprintf(cbuf, "<establish-resets>%s</establish-resets>", tcpStats->establishResets.c_str());
        cprintf(cbuf, "<currently-established>%i</currently-established>", (int) tcpConnections->size());
        cprintf(cbuf, "<in-segments>%s</in-segments>", tcpStats->inSegments.c_str());
        cprintf(cbuf, "<out-segments>%s</out-segments>", tcpStats->outSegments.c_str());
        cprintf(cbuf, "<retransmitted-segments>%s</retransmitted-segments>", tcpStats->retransmittedSegments.c_str());
        cprintf(cbuf, "<in-errors>%s</in-errors>", tcpStats->inErrors.c_str());
        cprintf(cbuf, "<out-resets>%s</out-resets>", tcpStats->outResets.c_str());
        cprintf(cbuf, "</statistics>");
        cprintf(cbuf, "</tcp>");

        yang_stmt *yangSpec = clicon_dbspec_yang(h);
        int res = clixon_xml_parse_string(cbuf_get(cbuf), YB_MODULE, yangSpec, &xstate, nullptr);
        if (res < 0)
            throw std::runtime_error("xml assign parse error");


        cbuf_free(cbuf);
        cbuf = nullptr;

        delete tcpStats;
        tcpStats = nullptr;

        for(auto connection : *tcpConnections) {
			delete connection;
		}
		delete tcpConnections;
		tcpConnections = nullptr;

        // match xpath filter
        //xpath_tree *xpath_tree;

        //if(xpath_parse(xpath,&xpath_tree) < 0)
        //  throw std::runtime_error("xml path tree error");

        return 0;

    } catch (std::exception &e) {
    	if(cbuf != nullptr) {
    		cbuf_free(cbuf);
    		cbuf = nullptr;
    	}

    	if(tcpStats != nullptr) {
    		delete tcpStats;
    		tcpStats = nullptr;
    	}

    	if(tcpConnections != nullptr) {
    		for(auto connection : *tcpConnections) {
    			delete connection;
    		}
    		delete tcpConnections;
    		tcpConnections = nullptr;
    	}

        clicon_err(OE_FATAL, errno, " %s", e.what());
        return -1;
    }
}
