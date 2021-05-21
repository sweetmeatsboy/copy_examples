#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "Windows.h"
#include "WinSock2.h"
#include "Ws2tcpip.h"
typedef int socklen_t;
//typedef char* receiveBufer_t;

#include <RoboCatShared.h>

#include <memory>

#include <vector>
#include <unordered_map>
#include <string>
#include <list>
#include <queue>
#include <deque>
#include <unordered_set>
#include <cassert>

#include <random>
#include <string>

using namespace std;
#include "NetworkManagerServer.h"
#include "ReplicationManagerServer.h"
#include "Server.h"

<<<<<<< HEAD
#include "ClientProxy.h"
=======
#include "ClientProxy.h"
#include "MouseServer.h"
#include "RoboCatServer.h"
#include "YarnServer.h"
>>>>>>> MultiplayergameProgramming
