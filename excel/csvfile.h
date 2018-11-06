#ifndef __CSVFILE_H__
#define __CSVFILE_H__

#include <string>
#include <vector>

using namespace std;

class CSVFile {
    public:
        typedef vector<string> ColumnListType;
        typedef vector<string> RowDataType;
        typedef vector<string> GenStringVectorType;
        typedef vector<RowDataType> SpreadSheetType;

        CSVFile( const string& file);
        CSVFile( const CSVFile& );
        ~CSVFile(){};

        void setDelimiter(char delim);
        ColumnListType getColumns();
        void showColumns();
        void getRow( RowDataType& r );
        string getDataByName( const string& col, const RowDataType& r );
        void reset();

    private:
        void parseRow( const char* buffer);
        void parseHeader( const char* buffer);
        void parse( GenStringVectorType& v, const char* buffer);
        string csvfile_;
        char delim_;
        ColumnListType columns_;
        SpreadSheetType spreadsheet_;
        SpreadSheetType::iterator it_;
};
#endif
