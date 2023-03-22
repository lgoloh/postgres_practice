#include "exerciser.h"
#include "utils.h"

int main (int argc, char *argv[]) 
{

  //Allocate & initialize a Postgres connection object
  connection *C;

  try{
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    C = new connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (C->is_open()) {
      cout << "Opened database successfully: " << C->dbname() << endl;
    } else {
      cout << "Can't open database" << endl;
      return 1;
    }
    //drop all tables before recreating
    cleanupDB(*C);
    createDBTables(*C);
    initAllTables(*C);
  } catch (const std::exception &e){
    cerr << e.what() << std::endl;
    return 1;
  }

  exercise(C);


  //Close database connection
  C->disconnect();

  return 0;
}


