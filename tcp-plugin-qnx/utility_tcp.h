#ifndef CLIXON_PLUGIN_TCP_UTILITY_TCP_H
#define CLIXON_PLUGIN_TCP_UTILITY_TCP_H


#include <string>
#include <list>

class TCPStats {
public:
    std::string activeOpens;
    std::string passiveOpens;
    std::string attemptFails;
    std::string establishResets;
    std::string inSegments;
    std::string outSegments;
    std::string retransmittedSegments;
    std::string inErrors;
    std::string outResets;

    TCPStats() = default;

    ~TCPStats() = default;
};

class TCPStatisticsManager {
public:
    static TCPStats *readStatistics();
};


class TCPAddress {
public:
    std::string ipAddress;
    std::string port;

    TCPAddress() = default;
    TCPAddress(std::string ipAddress, std::string port):ipAddress(std::move(ipAddress)), port(std::move(port)){
    }
};

class TCPConnection {
public:
    TCPAddress *localAddress = nullptr;
    TCPAddress *remoteAddress = nullptr;
    std::string conState;

    TCPConnection() = default;

    ~ TCPConnection() {
		delete localAddress;
		localAddress = nullptr;

		delete remoteAddress;
		remoteAddress = nullptr;
    }
};


class TCPConnectionManager {
public:

    static std::list<TCPConnection *> * readConnections();
};


#endif //CLIXON_PLUGIN_TCP_UTILITY_TCP_H
