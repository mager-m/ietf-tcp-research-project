#include <fstream>
#include <regex>
#include "utility_tcp.h"

TCPStats *TCPStatisticsManager::readStatistics() {
    std::ifstream fp("/proc/net/snmp", std::fstream::in);
    if (!fp) {
        throw std::runtime_error("Cannot open /proc/net/snmp");
    }
    auto *tcpStat = new TCPStats();
    std::string line;
    bool isTcpHeader = true;
    while (std::getline(fp, line)) {
        if (line.compare(0, 4, "Tcp:") == 0) {
            if (!isTcpHeader) {
                std::string skip;
                std::stringstream ss(line.substr(5));
                ss >> skip >> skip >> skip >> skip >> tcpStat->activeOpens >> tcpStat->passiveOpens
                   >> tcpStat->attemptFails >> tcpStat->establishResets >> tcpStat->currentlyEstablished
                   >> tcpStat->inSegments >> tcpStat->outSegments >> tcpStat->retransmittedSegments
                   >> tcpStat->inErrors >> tcpStat->outResets;
            }
            isTcpHeader = false;
        }
    }
    fp.close();

    return tcpStat;
}


TCPAddress::TCPAddress(const std::string &rawAddress) {
    const std::regex r("(..)(..)(..)(..):(....)");
    std::smatch sm;
    if (std::regex_search(rawAddress, sm, r)) {
        // ip
        this->ipAddress.append(std::to_string(stoi(sm[4], nullptr, 16)));
        this->ipAddress.append(".");
        this->ipAddress.append(std::to_string(stoi(sm[3], nullptr, 16)));
        this->ipAddress.append(".");
        this->ipAddress.append(std::to_string(stoi(sm[2], nullptr, 16)));
        this->ipAddress.append(".");
        this->ipAddress.append(std::to_string(stoi(sm[1], nullptr, 16)));

        //port
        this->port.append(std::to_string(stoi(sm[5], nullptr, 16)));
    }
}


std::list<TCPConnection *> TCPConnectionManager::readConnections() {
    // -> proc/net/tcp -> https://www.kernel.org/doc/Documentation/networking/proc_net_tcp.txt
    std::ifstream fp("/proc/net/tcp", std::fstream::in);
    if (!fp) {
        throw std::runtime_error("Cannot open /proc/net/tcp");
    }
    std::string line;
    bool isHeader = true;
    std::list<TCPConnection *> connectionList;
    while (std::getline(fp, line)) {
        if (!isHeader) {

            std::string skip, tmpLocalAddress, tmpRemoteAddress, tmpConState;
            std::stringstream ss(line);
            ss >> skip >> tmpLocalAddress >> tmpRemoteAddress >> tmpConState;

            if (tmpConState == "01") {  // 01= Established
                auto tcpCon = new TCPConnection();
                tcpCon->localAddress = new TCPAddress(tmpLocalAddress);
                tcpCon->remoteAddress = new TCPAddress(tmpRemoteAddress);
                tcpCon->conState = static_cast<TCPConState>(stoi(tmpConState, nullptr, 16));
                connectionList.push_back(tcpCon);
            }
        }
        isHeader = false;
    }

    return connectionList;
}

