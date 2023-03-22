#ifndef __UTILS__
#define __UTILS__

#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <pqxx/pqxx>

using std::vector;
using std::string;

/* #define PLAYER "\"PLAYER\""
#define TEAM "\"TEAM\""
#define STATE "\"STATE\""
#define COLOR "\"COLOR\"" */

using namespace std;
using namespace pqxx;
extern int last_playerID;
extern int last_teamID;
extern int last_stateID;
extern int last_colorID;

/*
 * Initializes table attributes
 */
vector<pair<string, string> > getPlayerAttributes();

vector<pair<string, string> > getTeamAttributes();

vector<pair<string, string> > getStateAttributes();

vector<pair<string, string> > getColorAttributes();

/**
 * 
 * Helper Functions
 * 
 */
void tokenize(string & input, string & delim, vector<string> & tokens, int start_indx);

vector<string> parse(string data, string delim);

string addSingleQuotes(string input);

vector<string> parseTextFiles(string filename, int & last_id);



/*
 * Query Handlers 
 */ 

//Create string of attributes from attribute vector
string getAttributeString(vector<pair<string, string> > & attr);

//Generates a query string to create a table based on the vector of attributes 
//t_name: name of the table
//attributes: vector of attibute:domain pairs (first mapping must be the primary key)
string buildCreateQuery(string & t_name, vector<pair<string, string> > attributes);

//Generates a query string to insert a row into a table 
//params:
//t_name: name of table to insert into
//attributes: vector of attibute:domain pairs
//values: string of value items to insert into table 
string buildInsertQuery(string & t_name, 
  vector<pair<string, string> > & attributes, string & values);

stringstream buildSelectQuery(vector<string> & attributes, vector<string> & tables);

void printQueryResults(result * res, vector<string> & attributes);

/*
 * Table Handlers
 */
void createDBTables(connection & db_conn);

void initDBTable(connection & db_conn, string file_name, string t_name);

void initAllTables(connection & db_conn);

void cleanupDB(connection & db_conn);

#endif