#include "exerciser.h"

void exercise(connection *C)
{
    /* cout << "Test 1\n";
    query1(C, 1, 35, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    cout << "Test 2\n";
    query1(C, 1, 35, 40, 1, 10, 20, 1, 2, 10, 0, 0, 0, 0, 0, 0, 1, 0, 1.0);
    cout << "Test 3\n";
    query2(C, "Gold");
    cout << "Test 4\n";
    query2(C, "Maroon");
    cout << "Test 5\n";
    query3(C, "Duke");  //All Duke players with descending order of PPG
    cout << "Test 6\n";
    query4(C, "VA", "Maroon"); //All VirginiaTech players
    cout << "Test 7\n";
    query4(C, "VA", "Orange"); //All Virginia players
    cout << "Test 8\n";
    query5(C, 2); //Teams and team players with wins > 2;
    cout << "Test 9\n";
    query5(C, 8); //Teams and team players with wins > 8;
    cout << "Test 10\n";
    query5(C, 11); //Teams and team players with wins > 11; */



    cout << "Test 1\n";
    query1(C, 1, 35, 40, 1, 10, 20, 1, 2, 10, 0, 0, 0, 0, 0, 0, 1, 0, 1.0);
    cout << "Test 2\n";
    query1(C, 1, 35, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    cout << "Test 3\n";
    query2(C, "Gold") ;
    cout << "Test 4\n";
    query3(C, "GeorgiaTech");
    cout << "Test 5\n";
    query4(C, "NC", "DarkBlue");
    cout << "Test 6\n";
    query5(C, 10) ;

    /* cout << "Test 7, adding new color, Indigo\n";
    add_color(C, "Indigo");
    cout << "Test 8, adding new color, Lavendar\n";
    add_color(C, "Lavendar");
    cout << "Test 9, adding new state, CA\n";
    add_state(C, "CA");
    cout << "Test 10, adding new state, WI\n";
    add_state(C, "WI");
    cout << "Test 11, adding new team in WI with color Indigo\n";
    add_team(C, "WITeam", 12, 9, 9, 9);
    cout << "Test 12, adding new team in CA with color Lavendar\n";
    add_team(C, "CATeam", 11, 10, 9, 9);
    

    cout << "Test 13\n";
    query2(C, "Indigo");
    cout << "Test 14\n";
    query2(C, "Lavendar");
    cout << "Test 15, adding new player in CA team\n";
    add_player(C, 17, 50, "Monkey D", "Luffy", 50, 10, 0, 0, 1.0, 1.0);
    cout << "Test 16\n";
    query5(C, 5);
    cout << "Test 17\n";
    query1(C, 1, 35, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    cout << "Test 18\n";
    query1(C, 1, 10, 20, 1, 5, 10, 1, 7, 10, 0, 0, 0, 1, 0.2, 1.0, 1, 0.5, 3.0);
    cout << "Test 19\n";
    query1(C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0); */
}
