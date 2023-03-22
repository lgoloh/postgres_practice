#include "query_funcs.h"
#include "utils.h"
#include "table_attr.h"

void add_player(connection *C, int team_id, int jersey_num, string first_name, string last_name, int mpg, int ppg, int rpg, int apg, double spg, double bpg) {
    string table = PLAYER;
    last_playerID += 1;
    vector<pair<string, string> > attributes = getPlayerAttributes();

    stringstream values_builder;
    values_builder << "(" << last_playerID << ", " << team_id << ", " << jersey_num << ", " 
        << addSingleQuotes(first_name) << ", " << addSingleQuotes(last_name)
        << ", " << mpg << ", " << ppg << ", " << rpg << ", " << apg << ", " 
        << spg << ", " << bpg << ")";

    string values = values_builder.str();
    string query = buildInsertQuery(table, attributes, values);
    
    work w(*C);
    w.exec(query);
    w.commit();

}

void add_team(connection *C, string name, int state_id, int color_id, int wins, int losses)
{
    string table = TEAM;
    last_teamID += 1;
    vector<pair<string, string> > attributes = getTeamAttributes();

    stringstream values_builder;
    values_builder << "(" << last_teamID << ", " << addSingleQuotes(name) << ", " <<  state_id << ", " 
    << color_id << ", " << wins << ", " << losses << ")";

    string values = values_builder.str();
    string query = buildInsertQuery(table, attributes, values);

    work w(*C);
    w.exec(query);
    w.commit();
}


void add_state(connection *C, string name)
{
    string table = STATE;
    last_stateID += 1;
    vector<pair<string, string> > attributes = getStateAttributes();

    stringstream values_builder;
    values_builder << "(" << last_stateID << ", " << addSingleQuotes(name) << ")";
    string values = values_builder.str();

    string query = buildInsertQuery(table, attributes, values);

    work w(*C);
    w.exec(query);
    w.commit();
    cout << "next last ID: " << last_stateID << endl;
}


void add_color(connection *C, string name)
{
    string table = COLOR;
    last_colorID += 1;
    vector<pair<string, string> > attributes = getColorAttributes();

    stringstream values_builder;
    values_builder << "(" << last_colorID << ", " << addSingleQuotes(name) << ")";
    string values = values_builder.str();

    string query = buildInsertQuery(table, attributes, values);

    work w(*C);
    w.exec(query);
    w.commit();
}

void addCondition(stringstream & query, int isEnabled, int max_val, int min_val, string attr) {
  if (isEnabled) {
        if (query.tellp() == streampos(0)) {
            query << "(" << min_val << " <= " << attr << " AND " << attr << " <= " << max_val << ")";
        } else {
            query << " AND " << "(" << min_val << " <= " << attr << " AND " << attr << " <= " << max_val << ")";
        }
    }
}
/*
 * All use_ params are used as flags for corresponding attributes
 * a 1 for a use_ param means this attribute is enabled (i.e. a WHERE clause is needed)
 * a 0 for a use_ param means this attribute is disabled
 */
void query1(connection *C,
	    int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg,
            int use_rpg, int min_rpg, int max_rpg,
            int use_apg, int min_apg, int max_apg,
            int use_spg, double min_spg, double max_spg,
            int use_bpg, double min_bpg, double max_bpg
            )
{
    nontransaction trans(*C);
    stringstream query;
    query << "SELECT * FROM " << PLAYER;
    stringstream conditions;

    addCondition(conditions, use_mpg, max_mpg, min_mpg, MPG);
    addCondition(conditions, use_ppg, max_ppg, min_ppg, PPG);
    addCondition(conditions, use_rpg, max_rpg, min_rpg, RPG);
    addCondition(conditions, use_apg, max_apg, min_apg, APG);
    addCondition(conditions, use_spg, max_spg, min_spg, SPG);
    addCondition(conditions, use_bpg, max_bpg, min_bpg, BPG);

    if (conditions.tellp() != streampos(0)) {
        query << " WHERE " << conditions.str() << ";";
    } else {
        return;
    }

    result res(trans.exec(query.str()));
    vector<string> attr;
    attr.reserve(11);
    vector<pair<string, string> > attributes = getPlayerAttributes();
    for (int i = 0; i < attributes.size(); i++) {
        attr.push_back(attributes.at(i).first);
    }
    if (!res.empty()) {
        printQueryResults(&res, attr);
    }
}


void query2(connection *C, string team_color)
{
    //SELECT "TEAM"."NAME" as "NAME" FROM "TEAM", "COLOR" WHERE "TEAM"."COLOR_ID" = "COLOR"."COLOR_ID" AND "COLOR"."NAME" = team_color;
    nontransaction trans(*C);
    vector<string> attributes;
    stringstream attr;
    attr << TEAM << "." << NAME;
    attributes.push_back(attr.str());
    
    vector<string> tables;
    tables.push_back(TEAM);
    tables.push_back(COLOR);

    stringstream query = buildSelectQuery(attributes, tables);
    query << TEAM << "." << COLOR_ID << " = " << COLOR << "." << COLOR_ID << " AND "
    << COLOR << "." << NAME << " = " << addSingleQuotes(team_color) << ";";
    
    result res(trans.exec(query.str()));
    if (!res.empty()) {
        printQueryResults(&res, attributes);
    }
}


void query3(connection *C, string team_name)
{
    //SELECT "FIRST_NAME", "LAST_NAME" FROM "PLAYER", "TEAM" WHERE "PLAYER"."TEAM_ID" = "TEAM"."TEAM_ID" AND "NAME" = 'Duke' ORDER BY "PPG" DESC;
    nontransaction trans(*C);
    vector<string> attributes;
    attributes.reserve(2);
    attributes.push_back(FIRST_NAME);
    attributes.push_back(LAST_NAME);

    vector<string> tables;
    tables.reserve(2);
    tables.push_back(PLAYER);
    tables.push_back(TEAM);

    stringstream query = buildSelectQuery(attributes, tables);
    query << PLAYER << "." << TEAM_ID << " = " << TEAM << "." << TEAM_ID << " AND "
    << NAME << " = " << addSingleQuotes(team_name) << " ORDER BY " << PPG << "DESC;";

    result res(trans.exec(query.str()));
    if (!res.empty()) {
        printQueryResults(&res, attributes);
    }
}


void query4(connection *C, string team_state, string team_color)
{

    //Example: SELECT "UNIFORM_NUM", "FIRST_NAME", "LAST_NAME" FROM "PLAYER", "TEAM", "STATE", "COLOR" WHERE "PLAYER"."TEAM_ID" = "TEAM"."TEAM_ID" AND "TEAM"."STATE_ID" = "STATE"."STATE_ID" AND "TEAM"."COLOR_ID" = "COLOR"."COLOR_ID" AND "STATE"."NAME" = 'VA' AND "COLOR"."NAME" = 'Maroon';
    nontransaction trans(*C);
    vector<string> attributes;
    attributes.reserve(3);
    attributes.push_back(UNIFORM_NUM);
    attributes.push_back(FIRST_NAME);
    attributes.push_back(LAST_NAME);

    vector<string> tables;
    tables.reserve(4);
    tables.push_back(PLAYER);
    tables.push_back(TEAM);
    tables.push_back(STATE);
    tables.push_back(COLOR);

    stringstream query = buildSelectQuery(attributes, tables);
    query << PLAYER << "." << TEAM_ID << " = " << TEAM << "." << TEAM_ID << " AND "
    << TEAM << "." << STATE_ID << " = " << STATE << "." << STATE_ID << " AND " 
    << TEAM << "." << COLOR_ID << " = " << COLOR << "." << COLOR_ID << " AND "
    << STATE << "." << NAME << " = " << addSingleQuotes(team_state) << " AND "
    << COLOR << "." << NAME << " = " << addSingleQuotes(team_color) << ";";

    result res(trans.exec(query.str()));
    if (!res.empty()) {
        printQueryResults(&res, attributes);
    }
}



void query5(connection *C, int num_wins)
{
    //SELECT "FIRST_NAME", "LAST_NAME", "TEAM"."NAME", "WINS" FROM "PLAYER", "TEAM" WHERE "PLAYER"."TEAM_ID" = "TEAM"."TEAM_ID" AND "WINS" > 2;
    nontransaction trans(*C);
    vector<string> attributes;
    stringstream attr;
    attr << TEAM << "." << NAME;
    attributes.reserve(4);
    attributes.push_back(FIRST_NAME);
    attributes.push_back(LAST_NAME);
    attributes.push_back(attr.str());
    attributes.push_back(WINS);

    vector<string> tables;
    tables.reserve(2);
    tables.push_back(PLAYER);
    tables.push_back(TEAM);

    stringstream query = buildSelectQuery(attributes, tables);
    query << PLAYER << "." << TEAM_ID << " = " << TEAM << "." << TEAM_ID << " AND "
    << WINS " > " << num_wins << ";";

    result res(trans.exec(query.str()));
    if (!res.empty()) {
        printQueryResults(&res, attributes);
    }
}
