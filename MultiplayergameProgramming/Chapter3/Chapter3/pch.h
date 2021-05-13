#ifndef PCH_H
#define PCH_H

#include <stdio.h>
#include <string>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <queue>
#include <deque>
#include <unordered_map>
#include<unordered_set>
#include <cassert>


using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::queue;
using std::list;
using std::deque;
using std::unordered_map;
using std::string;
using std::unordered_set;

typedef int socklen_t;

using namespace std;


#include "SocketAddress.h"
#include "StringUtils.h"
#include "TCPSocket.h"
#include "UDPSocket.h"
#include "SocketUtil.h"
#endif //PCH_H
