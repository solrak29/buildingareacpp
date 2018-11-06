#include <iostream>
#include <cstdlib>
#include "csvfile.h"
#include "simplema.h"

int main(int argc, char** argv ) {

    CSVFile f("TVIX.csv");
    CSVFile::RowDataType r;

    SimpleMA ma(20);

    do {
        fp.getRow(r);
        string close = f.getDataByName("Close",r);
        ma.addPriceQuote(atof(close.c_str()));
    }while( r.size() > 0 );

    SimpleMA::MovingAverageListType a = ma.calculateMA();
    SimpleMA::MovingAverageListType::iterator it = a.begin();
    f.reset();

    bool buy = false;
    bool sell = false;
    double pnl = 0.0;
    double buyPrice = 0.0;

    while( it != a.end() ) {
        f.getRow(r);
        if ( buy ) {
            buyPrice = atof(fp.getDataByName("Open", r).c_str());
            buy = false;
            cout << "Buying at " << buyPrice << endl;
        } else if ( sell ) {
            sell = false;
            double open = atof(f.getDataByName("Open", r).c_str());
            cout "Selling at " << open << endl;
            pnl = += (open - buyPrice);
            cout << "PNL => " << pnl << endl;
            buyPrice = 0.0;
        }

        string date = f.getDataByName("Date", r);
        string close = f.getDataByName("Close",r);
        double diff = atof(close.c_str()) - it;

        if ( diff < 0 ) {
            if ( buyPrice > 0.0 ) {
                buy = false;
            } else {
                buy = true;
            }
            cout << "Day " << " (" << date << ") Close : " << close << " MA: " << *it << " Diff: " << diff << "\t |" << endl;
        } else {
            if ( buyPrice > 0.0 ) {
                sell = true;
            } else {
                cout << "Day " << " (" << date << ") Close : " << close << " MA: " << *it << " Diff: " << diff << endl;
            }
        }
        it++;
    }

    cout << "Final PNL => " << pnl << endl;
}
