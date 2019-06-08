#include "veritiontest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stack>

using namespace std;

VeritionTest::VeritionTest( string quoteFileName, string tradeFileName){

    ifstream processFile(quoteFileName);
    string line;
    while (getline(processFile, line)){
        stringstream strQuoteData(line);
        string value;
        int column = 0;
        Quotes q;
        while(getline(strQuoteData,value,',')){
            switch (column){
                case 0:
                    q.time = atoi(value.c_str());
                    break;
                case 1:
                    q.symbol = value;
                    break;
                case 2:
                    q.bid = atof(value.c_str());
                case 3:
                    q.ask = atof(value.c_str());
                default:
                    break;
            };

            column++;
        }
        _quotes.push_back(q);
    }

    processFile.close();
    processFile.open(tradeFileName);
    while (getline(processFile, line)){
    stringstream strQuoteData(line);
        string value;
        int column = 0;
        Trades t;
        while(getline(strQuoteData,value,',')){
            switch (column){
                case 0:
                    t.time = atoi(value.c_str());
                    break;
                case 1:
                    t.symbol = value;
                    break;
                case 2:
                    t.side = value.at(0);
                    break;
                case 3:
                    t.price = atof(value.c_str());
                    break;
                case 4:
                    t.qty = atoi(value.c_str());
                    break;
                default:
                    break;
            };

            column++;
        }
        map<string, vector<Trades>>::iterator it;
        t.liquidity = 'Z';
        t.bid = 0.0;
        t.ask = 0.0;
        it = _tradeMap.find(t.symbol);
        if ( it == _tradeMap.end()){
            vector<Trades> _trade;
            _trade.push_back(t);
            _tradeMap.insert(pair<string,vector<Trades>>(t.symbol, _trade)); 
        } else {
            it->second.push_back(t);
        }
    }

}

void
VeritionTest::run() {
    applyQuotes();
    //dumpTradeMap();
    pairTrades();
}

void
VeritionTest::dumpTradeMap(){
    
    for(TradeMapType::iterator it = _tradeMap.begin(); it != _tradeMap.end(); it++ ) {
        for (TradeListType::iterator bit = it->second.begin(); bit != it->second.end(); bit++ ) {
            cout << bit->symbol << "," << bit->time << "," << bit->side << "," << bit->price << "," << bit->bid << "," << bit->ask << "," << bit->qty << "," << bit->liquidity << endl;
        }
    }
    
}

void
VeritionTest::pairTrades(){
    //
    // match open/close trade pairs
    //
    TradeMapType::iterator it = _tradeMap.begin();
    TradeListType openingTrades;
    while (it != _tradeMap.end()){
        TradeListType t = it->second;
        TradeListType::iterator nextTrade = t.begin();
        TradeListType::iterator firstTrade = t.begin(); // points to first trade out
        char pos_side = firstTrade->side; // side we are opening with
        nextTrade++;
        while( nextTrade != t.end() ) {
            if ( nextTrade->side != pos_side ) {
                // closing price is smaller than open price
                if ( firstTrade->qty > nextTrade->qty ) {
                    cout << firstTrade->time << ","
                         << nextTrade->time << ","
                         << firstTrade->symbol << ","
                         << nextTrade->qty << ","
                         << nextTrade->bid << ","
                         << nextTrade->ask << ","
                         << firstTrade->liquidity
                         << endl;
                } else {
                }
            }
            nextTrade++;
        }
        it++;
    }
}

void
VeritionTest::applyQuotes(){
    //
    // tag all the trades with appropiate liquidity and bid/ask price 
    //
    for( QuotesListType::iterator qit = _quotes.begin(); qit != _quotes.end(); qit++)
    {
        TradeMapType::iterator it;
        it = _tradeMap.find(qit->symbol);
        if ( it != _tradeMap.end() ) {
            TradeListType::iterator t = it->second.begin();

            // iterate thorugh all the executions for this symbol
            while( t != it->second.end()){
                cout << "Processing symbol " << t->symbol << " at time " << t->time << " versus " << qit->time << endl;
                if ( t->time <= qit->time && t->liquidity == 'Z'){
                    t->bid = qit->bid;
                    t->ask = qit->ask;
                    if ( t->side == 'B'){
                        if ( t->price <= qit->bid ){
                            t->liquidity = 'P';
                        }else if (t->price >= qit->ask ) {
                            t->liquidity = 'A';
                        } else {
                            t->liquidity = 'U';
                        }
                    } else if ( t->side == 'S'){
                        if ( t->price >= qit->ask ) {
                            t->liquidity = 'P';
                        } else if (t->price <= qit->bid) {
                            t->liquidity = 'A';
                        } else {
                            t->liquidity = 'U';
                        }
                    } else {
                       cerr << "Undefined side:" << t->side << endl;
                    }
                    cout << "Updating symbol with bid " << t->bid << " ask " << t->ask << "liquidity" << t->liquidity << endl;
                }
                t++;
            }
        } else {
            cout << "No symbol name " << qit->symbol << endl;
        }
    } // done liquidity processing
}

