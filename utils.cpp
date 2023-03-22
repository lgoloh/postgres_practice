#include "utils.h"
#include "table_attr.h"
#include "algorithm"
int last_playerID;
int last_teamID;
int last_stateID;
int last_colorID;

vector<pair<string, string> > getPlayerAttributes() {
  vector<pair<string, string> > player_attr;
  player_attr.push_back(make_pair(PLAYER_ID, "INT"));
  player_attr.push_back(make_pair(TEAM_ID, "INT"));
  player_attr.push_back(make_pair(UNIFORM_NUM, "INT"));
  player_attr.push_back(make_pair(FIRST_NAME, "TEXT"));
  player_attr.push_back(make_pair(LAST_NAME, "TEXT"));
  player_attr.push_back(make_pair(MPG, "REAL"));
  player_attr.push_back(make_pair(PPG, "REAL"));
  player_attr.push_back(make_pair(RPG, "REAL"));
  player_attr.push_back(make_pair(APG, "REAL"));
  player_attr.push_back(make_pair(SPG, "REAL"));
  player_attr.push_back(make_pair(BPG, "REAL"));
  return player_attr;
}

vector<pair<string, string> > getTeamAttributes() {
  vector<pair<string, string> > team_attr;
  team_attr.push_back(make_pair(TEAM_ID, "INT"));
  team_attr.push_back(make_pair(NAME, "TEXT"));
  team_attr.push_back(make_pair(STATE_ID, "INT"));
  team_attr.push_back(make_pair(COLOR_ID, "INT"));
  team_attr.push_back(make_pair(WINS, "INT"));
  team_attr.push_back(make_pair(LOSSES, "INT"));
  return team_attr;
}

vector<pair<string, string> > getStateAttributes() {
  vector<pair<string, string> > state_attr;
  state_attr.push_back(make_pair(STATE_ID, "INT"));
  state_attr.push_back(make_pair(NAME, "TEXT"));
  return state_attr;
}


vector<pair<string, string> > getColorAttributes() {
  vector<pair<string, string> > color_attr;
  color_attr.push_back(make_pair(COLOR_ID, "INT"));
  color_attr.push_back(make_pair(NAME, "TEXT"));
  return color_attr;
}

/**
 * 
 * Helper Functions
 * 
 */
void tokenize(string & input, string & delim, vector<string> & tokens, int start_indx) {
    if (start_indx >= input.size()) {
        return;
    }
    size_t delim_pos = input.find(delim, start_indx);
    if (delim_pos == string::npos) {
        tokens.push_back(input.substr(start_indx));
        return;
    } else {
        tokens.push_back(input.substr(start_indx, delim_pos-start_indx));
        start_indx = delim_pos + 1;
        tokenize(input, delim, tokens, start_indx);
    }
}

vector<string> parse(string data, string delim) {
    vector<string> tokens;
    tokenize(data, delim, tokens, 0);
    return tokens;
}

string addSingleQuotes(string input) {
  string s;
  s.append("'");
  for (int j = 0; j < input.size(); j++) {
    if (input.at(j) == '\'') {
      s.push_back('\'');
    }
    s.push_back(input.at(j));
  }
  s.append("'");
  return s;
}


vector<string> parseTextFiles(string filename, int & last_id) {
  vector<string> values;
  string buffer;
  ifstream data(filename);
  string line("(");
  while(getline(data, buffer)) {
    vector<string> tokens = parse(buffer, " ");
    for (int i = 0; i < tokens.size(); i++) {
      string s = tokens.at(i);
      if (isalpha(s.at(0))) {
        s = addSingleQuotes(s);
      }
      line.append(s);
      if (i != tokens.size() - 1) {
        line.append(",");
        line.append(" ");
      } else {
        last_id = stoi(tokens.at(0));
        line.append(")");
      } 
    }
    values.push_back(line);
    line = "(";
  }
  return values;
}


string getAttributeString(vector<pair<string, string> > & attr) {
  stringstream attr_s;
  attr_s << "(";
  for (int i = 0; i < attr.size(); i++) {
    attr_s << attr.at(i).first;
    if (i != attr.size()-1) {
      attr_s << ",";
    }
  }
  attr_s << ")";
  return attr_s.str();
}

string buildQueryParts(vector<string> & args) {
    stringstream q_parts;
    for (int i = 0; i < args.size(); i++) {
      q_parts << args.at(i);
      if (i == args.size() - 1) {
          q_parts << " ";
      } else {
          q_parts << ", ";
      }
    }
    return q_parts.str();
}

string buildCreateQuery(string & t_name, vector<pair<string, string> > attributes) {
    stringstream query;
    query << "CREATE TABLE " << t_name << "(";
    for (int i = 0; i < attributes.size(); i++) {
      query << attributes.at(i).first << " " << attributes.at(i).second;
      if (i == 0) {
        query << " PRIMARY KEY";
      } 
      if (i == attributes.size() - 1) {
        query << " NOT NULL";
      } else {
        query << " NOT NULL,";
      }
    }
    query << ");";
    return query.str();
}


string buildInsertQuery(string & t_name, 
  vector<pair<string, string> > & attributes, string & values) {
    stringstream query;
    query << "INSERT INTO " << t_name << " " << getAttributeString(attributes)
    << " VALUES " << values << ";";
    string res = query.str();
    return res;
}


stringstream buildSelectQuery(vector<string> & attributes, vector<string> & tables) {
  stringstream query;
  query << "SELECT ";
  if (attributes.empty()) {
      query << "* ";
  } else {
      query << buildQueryParts(attributes);
  }
  query << "FROM " << buildQueryParts(tables) << "WHERE ";
  return query;
}

void printQueryResults(result * res, vector<string> & attr) {
  for (int i = 0; i < attr.size(); i++) {
    string s = attr.at(i);
    s.erase(remove(s.begin(), s.end(), '\"' ) ,s.end());
    size_t pos = s.find('.');
    if (pos != string::npos) {
      cout << s.substr(pos + 1);
    } else {
      cout << s;
    }
    if (i == attr.size() - 1) {
      cout << "\n";
    } else {
      cout << " ";
    }
  }
  for (result::const_iterator c = res->begin(); c != res->end(); ++c) {
    for (int i = 0; i < c->size(); i++) {
      if (strcmp(c[i].name(), "SPG") == 0 || strcmp(c[i].name(), "BPG") == 0) {
        if (strcmp(c[i].c_str(), "1") == 0 || strcmp(c[i].c_str(), "0") == 0) {
          //cout << "need a decimal point\n";
          cout << c[i] << "." << "0";
        } else {
          cout << c[i];
        }
      } else {
        cout << c[i];
      }
      if (i == c->size() - 1) {
        cout << "\n";
        } else {
          cout << " ";
        }
    }
  }
}


void createDBTables(connection & db_conn) {
  work W(db_conn);

  vector<pair<string, vector<pair<string, string> > > > all_attributes;
  all_attributes.reserve(4);
  all_attributes.push_back(make_pair(PLAYER, getPlayerAttributes()));
  all_attributes.push_back(make_pair(TEAM, getTeamAttributes()));
  all_attributes.push_back(make_pair(STATE, getStateAttributes()));
  all_attributes.push_back(make_pair(COLOR, getColorAttributes()));

  vector<pair<string, vector<pair<string, string> > > >::iterator it;
  for (it = all_attributes.begin(); it != all_attributes.end(); ++it) {
    string query = buildCreateQuery(it->first, it->second);
    W.exec(query);
  }

  W.commit();
}

void initDBTable(connection & db_conn, string file_name, string t_name) {
  work W(db_conn);
  vector<pair<string, string> > attributes;
  vector<string> values;
  if (t_name == PLAYER) {
    attributes = getPlayerAttributes();
    values = parseTextFiles(file_name, last_playerID);
  } else if (t_name == TEAM) {
    attributes = getTeamAttributes();
    values = parseTextFiles(file_name, last_teamID);
  } else if (t_name == STATE) {
    attributes = getStateAttributes();
    values = parseTextFiles(file_name, last_stateID);
  } else if (t_name == COLOR) {
    attributes = getColorAttributes();
    values = parseTextFiles(file_name, last_colorID);
  }

  stringstream query;
  for (int i = 0; i < values.size(); i++) {
    query << buildInsertQuery(t_name, attributes, values.at(i)) << " ";
  }
  W.exec(query.str());
  W.commit();
}

void initAllTables(connection & db_conn) {
  initDBTable(db_conn, "player.txt", PLAYER);
  initDBTable(db_conn, "team.txt", TEAM);
  initDBTable(db_conn, "state.txt", STATE);
  initDBTable(db_conn, "color.txt", COLOR);
}


void cleanupDB(connection & db_conn) {
  string sql = "DROP SCHEMA public CASCADE;";
  string sql2 = "CREATE SCHEMA public;";
  work W(db_conn);

  W.exec(sql);
  W.exec(sql2);
  W.commit();
}