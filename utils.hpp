#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <pqxx/pqxx>

using std::vector;
using std::string;

#define PLAYER "\"PLAYER\""
#define TEAM "\"TEAM\""
#define STATE "\"STATE\""
#define COLOR "\"COLOR\""

using namespace std;
using namespace pqxx;
int last_playerID;
int last_teamID;
int last_stateID;
int last_colorID;

/**
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

/*
 * Parse text files into list of comma-separated value strings;
 */
vector<string> parseTexts(string filename, int & last_id);



/*
 * Query Handlers 
 */ 

//Create string of attributes from attribute vector
string getAttributeString(vector<pair<string, string> > & attr);

//Generates a query string to create a table based on the vector of attributes 
//t_name: name of the table
//attributes: vector of attibute:domain pairs (first mapping must be the primary key)
string createTableQuery(string & t_name, vector<pair<string, string> > attributes);

//Generates a query string to insert a row into a table 
//params:
//t_name: name of table to insert into
//attributes: vector of attibute:domain pairs
//values: string of value items to insert into table 
string insertRowQuery(string & t_name, 
  vector<pair<string, string> > & attributes, string & values);

/*
 * Create DB tables
 */
void createDBTables(connection & db_conn);

void initDBTable(connection & db_conn, string file_name, string t_name);

void initAllTables(connection & db_conn);

/*
 * Drop all database tables
 */
void cleanupDB(connection & db_conn);

#endif