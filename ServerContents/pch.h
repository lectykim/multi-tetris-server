#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#pragma comment(lib,"..\\TetrisServer\\x64\\Debug\\TetrisServer.lib")
#else
#pragma comment(lib,"TetrisServer\\x64\Release\\TetrisServer.lib")
#endif

#include <unordered_map>
#include <array>



#include "../TetrisServer/pch.h"

