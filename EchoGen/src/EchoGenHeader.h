#pragma once

/* [insert every libraries you can think of here] */
// miscellaneous
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <random>
#include <functional>
#include <memory>
#include <iterator>
#include <filesystem>
#include <mutex>

// i/o
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

// containers
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <queue>
#include <stack>

// log
#include <EchoGen/Core/Log.h>

// windows specific
#ifdef ECHO_WINDOWS
#include <Windows.h>
#endif