#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <functional>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <unordered_map>
#include <algorithm>
using namespace std;

auto generarIdReserva = []() {
    srand(time(nullptr));
    return rand() % 900000 + 100000;
};