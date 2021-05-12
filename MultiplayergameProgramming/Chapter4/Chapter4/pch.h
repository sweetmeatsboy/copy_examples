#pragma once

#if _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#else

#endif


#include <stdio.h>
#include <iostream>

#include <WS2tcpip.h>
#include <Windows.h>
#include <winsock2.h>


#include <memory>
#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <string>
#include <queue>
#include <deque>
#include <cassert>


using namespace std;

#include "RoboMath.h"

#include "ByteSwap.h"

#include "MemoryBitStream.h"
#include "LinkingContext.h"
#include "MemoryStream.h"

