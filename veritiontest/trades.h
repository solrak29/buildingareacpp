#ifndef __TRADES_H__
#define __TRADES_H__

#include <string>
using namespace std;

struct Trades{
    int time;
    int ctime;
    string symbol;
    char side;
    double price;
    double bid;
    double ask;
    int qty;
    char liquidity;
    
};
#endif
