#pragma once

#include <stdio.h>
#include <iostream>
#include <random>
#include <bitset>
#include <sstream>
#include <iterator>
#include <algorithm>


typedef unsigned long long ulong;

ulong nextGeneration(ulong bord);

ulong nextGenerationV2(ulong bord);

ulong randULong();

void outBord(ulong bord);

std::mt19937_64 *mt;