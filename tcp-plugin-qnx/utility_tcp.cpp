#include <fstream>
#include <regex>
#include <sstream>
#include "utility_tcp.h"

using namespace std;

TCPStats *TCPStatisticsManager::readStatistics() {
    std::system("netstat -p TCP > /tmp/statistics.txt");
    
    std::ifstream fp("/tmp/statistics.txt", std::fstream::in);
    if (!fp) {
        throw std::runtime_error("Cannot open /tmp/statistics.txt");
        
    }

    std::stringstream buffer;
    buffer << fp.rdbuf();
    auto netstatOutput = buffer.str();

    fp.close();

    const std::regex connectionEstablished ("(?:[^|\\n])(?:\\s*)(\\d+) connections established \\(including accepts\\)");
    const std::regex connectionAccepts ("(?:[^|\\n])(?:\\s*)(\\d+) connection accepts");
    const std::regex passiveOpens ("(?:[^|\\n])(?:\\s*)(\\d+) connection accepts");
    const std::regex attemptFails ("(?:[^|\\n])(?:\\s*)(\\d+) embryonic connections dropped");
    const std::regex estblishResets ("(?:[^|\\n])(?:\\s*)(\\d+) connections closed \\(including (?:.*?) drops\\)");
    const std::regex inSegments ("(?:[^|\\n])(?:\\s*)(\\d+) packets received");
    const std::regex packetsSent ("(?:[^|\\n])(?:\\s*)(\\d+) packets sent");
    const std::regex packetsRetransmitted ("(?:[^|\\n])(?:\\s*)(\\d+) data packets \\(\\d+ bytes\\) retransmitted");
    const std::regex discardedBadChecksum ("(?:[^|\\n])(?:\\s*)(\\d+) discarded for bad checksums");
    const std::regex discardedBadHeaderOffset ("(?:[^|\\n])(?:\\s*)(\\d+) discarded for bad header offset fields");
    const std::regex discardedPacketTooShort ("(?:[^|\\n])(?:\\s*)(\\d+) discarded because packet too short");
    const std::regex outResets ("(?:[^|\\n])(?:\\s*)(\\d+) bad connection attempts");

    std::smatch sm;

    auto *tcpStat = new TCPStats();


    if (regex_search(netstatOutput, sm, connectionEstablished)){
        tcpStat->activeOpens = sm[1];
    }
    if (regex_search(netstatOutput, sm, connectionAccepts)){
        tcpStat->activeOpens = std::to_string(stoi(tcpStat->activeOpens) - stoi(sm[1]));
    }

    if (regex_search(netstatOutput, sm, connectionAccepts)){
        tcpStat->passiveOpens = sm[1];
    }

    if (regex_search(netstatOutput, sm, attemptFails)){
        tcpStat->attemptFails = sm[1];
    }

    if (regex_search(netstatOutput, sm, estblishResets)){
        tcpStat->establishResets = sm[1];
    }

    if (regex_search(netstatOutput, sm, inSegments)){
        tcpStat->inSegments = sm[1];
    }

    if (regex_search(netstatOutput, sm, packetsSent)){
        tcpStat->outSegments = sm[1];
    }
    if (regex_search(netstatOutput, sm, packetsRetransmitted)){
        tcpStat->outSegments = std::to_string(stoi(tcpStat->outSegments) - stoi(sm[1]));
    }

    if (regex_search(netstatOutput, sm, packetsRetransmitted)){
        tcpStat->retransmittedSegments = sm[1];
    }

    if (regex_search(netstatOutput, sm, discardedBadChecksum)){
        tcpStat->inErrors = sm[1];
    }
    if (regex_search(netstatOutput, sm, discardedBadHeaderOffset)){
        tcpStat->inErrors =  std::to_string(stoi(tcpStat->inErrors) + stoi(sm[1]));
    }
    if (regex_search(netstatOutput, sm, discardedPacketTooShort)){
        tcpStat->inErrors = std::to_string(stoi(tcpStat->inErrors) + stoi(sm[1]));
    }

    if (regex_search(netstatOutput, sm, outResets)){
            tcpStat->outResets = sm[1];
    }

    return tcpStat;
}


std::list<TCPConnection *> * TCPConnectionManager::readConnections() {
    std::system("netstat -n > /tmp/connectionList.txt");

    std::ifstream fp("/tmp/connectionList.txt", std::fstream::in);
    if (!fp) {
        throw std::runtime_error("Cannot open connectionList.txt");
    }

    std::stringstream buffer;
    buffer << fp.rdbuf();
    auto netstatOutput = buffer.str();
    fp.close();

    auto * connectionList = new std::list<TCPConnection *>();

    const std::regex r ("(?:^|\n)tcp(?:\\s+)(\\d+)(?:\\s+)(\\d+)(?:\\s+)([0-9\\.]+)\\.([0-9]+)(?:\\s+)([0-9\\.]+)\\.([0-9]+)(?:\\s+)ESTABLISHED");

    auto regex_begin = std::sregex_iterator(netstatOutput.begin(), netstatOutput.end(), r);
    auto regex_end = std::sregex_iterator();

    for(std::sregex_iterator i = regex_begin; i != regex_end; i++) {
    	std::smatch sm = *i;

    	auto tcpCon = new TCPConnection();
        tcpCon->localAddress = new TCPAddress(sm[3], sm[4]);
        tcpCon->remoteAddress = new TCPAddress(sm[5], sm[6]);
        tcpCon->conState = "ESTABLISHED";
        connectionList->push_back(tcpCon);
    }


    return connectionList;
}

