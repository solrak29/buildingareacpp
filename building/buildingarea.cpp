#include "building.h"
#include <iostream>
#include <vector>


using namespace std;

typedef vector<BUILDING_CONST::Building> BuildingListType;

// Assumming the Building list is sorted by x1
BUILDING_CONST::Unit
buildingArea( BuildingListType& list ) {
    BUILDING_CONST::Building save;
    int numBuildings = list.size();
    int area = 0;
    BuildingListType::iterator it = list.begin();
    int i = 0;
    while( it !=  list.end() )
    {
        if ( list[i].X2 > list[i+1].X1 ) { 
            if ( list[i+1].Y > list[i].Y ) {
                save = list[i];
                save.X1 = 0;
                area += (list[i+1].X1 - list[i].X1) * list[i].Y;
            } else {
                list.erase(list.begin()+1);
                i--;
            }
        } else {
            area += (list[i].X2 - list[i].X1) * list[i].Y;
        }
        it++;
    }
    if ( save.X1 > 0 || save.X2 > 0 ) {
        area += ( save.X2 - list[numBuildings-1].X2 ) * save.Y;
    }

    return area;
}

int main(int argc, char** argv ) {

    cout << "Loading vector of buildings" << endl;

    // Test 1
    //BUILDING_CONST::Building b1 { 1, 4, 1 };
    //BUILDING_CONST::Building b2 { 2, 3, 2 };
    //
    // Test 2
    BUILDING_CONST::Building b1 { 1, 6, 2 };
    BUILDING_CONST::Building b2 { 3, 4, 1 };

    BuildingListType buildList;
    buildList.push_back(b1);
    buildList.push_back(b2);

    BuildingListType::iterator it = buildList.begin();

    int count = 0;
    while( it != buildList.end() ) {
        cout << "Building " << count <<  " X1 " << it->X1 << endl; 
        count++;
        it++;
    }

    BUILDING_CONST::Unit a = buildingArea( buildList );
    cout << "Total area is : " << a << endl;
}
