#include "building.h"
#include <iostream>
#include <vector>


using namespace std;

typedef vector<BUILDING_CONST::Building> BuildingListType;

// Assumming the Building list is sorted by x1
BUILDING_CONST::Unit
buildingArea( BuildingListType& list ) {

    BUILDING_CONST::Building *save = NULL;
    int numBuildings = list.size();
    int area = 0;
    BuildingListType::iterator it = list.begin();
    BuildingListType::iterator nit = list.end();
    int i = 0;

    while( it != list.end() || save  )
    {
        if ( save ) {
            if (it == list.end() || save->x1 > it->x1 ) {
                area += ((it->x2 - it->x1) * it->y);
                delete save;
                save = NULL;
            }
            else {
                area += ((it->x2 - it->x1) * it->y);
                it++;
            }
        } else {
            nit = it;
            ++nit;
            if ( nit != list.end() ){
                if ( it->x2 > nit->x1 && nit->y > it->y) {
                        save = new BUILDING_CONST::Building();
                        save->x1 = nit->x2;
                        save->x2 = it->x2;
                        save->y = it->y;
                        it->x2 = nit->x1;
                } else if ( it->x2 > nit->x1 && nit->y < it->y) {
                        save = new BUILDING_CONST::Building();
                        save->x1 = nit->x1;
                        save->x2 = it->x2;
                        save->y = it->y;
                        it->x2 = nit->x1;
                        *nit = *save;
                        delete save;
                        save = NULL;
                }
            } 
            area += ((it->x2 - it->x1) * it->y);
            it++;
       }
   }

    return area;
}

int main(int argc, char** argv ) {

    BuildingListType buildList;
    cout << "Running Test Case 1: single tall building in middle of another..." << endl;
    // Test 1
    // Buidling inside a building should will be counted
    BUILDING_CONST::Building b1 { 1, 4, 1 };
    BUILDING_CONST::Building b2 { 2, 3, 2 };
    buildList.push_back(b1);
    buildList.push_back(b2);
    BUILDING_CONST::Unit a = buildingArea( buildList );

    cout << "Result => " << a << endl;
    if ( a == 5 ) {
        cout << "Passed" << endl;
    } else {
        cout << "Failed" << endl;
    }

    buildList.clear();
    cout << "Running Test Case 2: single small building in middle of another..." << endl;
    //
    // Test 2 building inside a complete buidling should not be counted 10.
    b1.x1=1;
    b1.x2=5;
    b1.y=2;

    b2.x1=2;
    b2.x2=3;
    b2.y=4;

    buildList.push_back(b1);
    buildList.push_back(b2);
    a = buildingArea( buildList );
    cout << "Result => " << a << endl;

    if ( a == 10 ) {
        cout << "Passed" << endl;
    } else {
        cout << "Failed" << endl;
    }

    buildList.clear();
    BUILDING_CONST::Building b3 { 6, 7, 1 };
    b1.x1=1;
    b1.x2=6;
    b1.y=2;

    b2.x1=3;
    b2.x2=4;
    b2.y=1;
    buildList.push_back(b1);
    buildList.push_back(b2);
    buildList.push_back(b3);
    a = buildingArea( buildList );
    cout << "Result => " << a << endl;

}
