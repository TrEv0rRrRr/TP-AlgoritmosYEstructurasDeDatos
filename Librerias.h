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
#include <ctime>
#include <iomanip>
using namespace std;
using namespace System;

auto generarIdReserva = []() {
    srand(time(nullptr));
    return rand() % 900000 + 100000;
};

auto generarIdFactura = []() {
    srand(time(nullptr));
    return rand() % 9000000 + 1000000;
    };