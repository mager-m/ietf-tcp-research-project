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
    std::string currentlyEstablished;
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

    explicit TCPAddress(const std::string &rawAddress);

};

enum TCPConState {
    UNDEFINED = 0,
    TCP_ESTABLISHED = 1,
    TCP_SYN_SENT = 2,
    TCP_SYN_RECV = 3,
    TCP_FIN_WAIT1 = 4,
    TCP_FIN_WAIT2 = 5,
    TCP_TIME_WAIT = 6,
    TCP_CLOSE = 7,
    TCP_CLOSE_WAIT = 8,
    TCP_LAST_ACK = 9,
    TCP_LISTEN = 10,
    TCP_CLOSING = 11,
    TCP_NEW_SYN_RECV = 12,
    TCP_MAX_STATES = 13
};

class TCPConnection {
public:
    TCPAddress *localAddress{};
    TCPAddress *remoteAddress{};
    TCPConState conState = UNDEFINED;

    TCPConnection() = default;

    ~ TCPConnection() = default;
};


class TCPConnectionManager {
public:

    static std::list<TCPConnection *> readConnections();
};


#endif //CLIXON_PLUGIN_TCP_UTILITY_TCP_H
