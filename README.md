# postgres_practice
A project to implement queries using the PostgreSQL C++ Client API, Libpqxx.

Goals: Practice writing SQL queries for a PostgreSQL database using Libpqxx.

This project builds a PostgreSQL database for ACC BasketBall Teams. The ACC_BBALL database has the following schema: ACC_BBALL(PLAYER, TEAM, STATE, COLOR);
The main tasks include: 
  1. A C++ program to read text files containing the entries (rows) for each table, and build the database by creating each table and adding entries.
  2. A C++ library (set of functions) which will provide an interface for a program to interact with the database (e.g. add rows to the tables and query for certain information).




### Queries: 
query_funcs.hpp: Defines the interface for interacting with the database
1. query1(): show all attributes of each player with average statistics that fall between the min and max (inclusive) for each enabled statistic
2. query2(): show the name of each team with the indicated uniform color
3. query3(): show the first and last name of each player that plays for the indicated team, ordered from highest to lowest ppg (points per game)
4. query4(): show uniform number, first name and last name of each player that plays in the indicated state and wears the indicated uniform color
5. query5(): show first name and last name of each player, and team name and number of wins for each team that has won more than the indicated number of games

### Sample Query:
```
Show the first and last name of each player that plays for GeorgiaTech, ordered from highest to lowest ppg (points per game)
query3(C, "GeorgiaTech"):

FIRST_NAME LAST_NAME
Josh Okogie
Ben Lammers
Tadric Jackson
Quinton Stephens
Josh Heath
Justin Moore
Christian Matthews
Corey Heyward
Sylvester Ogbonda
Kellen McCormick
Abdoulaye Gueye
Shaheed Medlock
Norman Harris
Jodan Price
Rand Rowland
```
