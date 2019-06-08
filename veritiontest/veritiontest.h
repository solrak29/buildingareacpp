#ifndef __VERITION_TEST_H__
#define __VERITION_TEST_H__

#include "quotes.h"
#include "trades.h"
#include <string>
#include <vector>
#include <map>

class VeritionTest {

    // Predefined types
    typedef vector<Quotes> QuotesListType;
    typedef vector<Trades> TradeListType;
    typedef map<string, TradeListType> TradeMapType; 
    typedef pair<string, TradeListType> TradeMapPairType;

    public:
        VeritionTest( string quoteFileName, string tradeFileName );
        void run();
        void results(){};
    private:
        void applyQuotes();
        void pairTrades();
        void dumpTradeMap();

        QuotesListType _quotes;
        TradeMapType _tradeMap;
};
#endif
