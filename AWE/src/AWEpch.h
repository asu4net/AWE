#pragma once

//--- std common includes ---
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>

//--- AWE common includes --- 
#include "AWE/Core/Core.h"

//--- Custom types ---
template<typename T>
using Ptr = std::shared_ptr<T>;

template<typename T>
using String = std::string;

template<typename T>
using Vector = std::vector<T>;

//--- Defines ---
#define MAKE_PTR std::make_shared