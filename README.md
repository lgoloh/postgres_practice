# postgres_practice
A project to implement queries using the PostgreSQL C++ Client API, Libpqxx.

Goals: Practice writing SQL queries for a PostgreSQL database using Libpqxx.

This project builds a PostgreSQL database for ACC BasketBall Teams. The ACC_BBALL database has the following schema: ACC_BBALL(PLAYER, TEAM, STATE, COLOR);
The main tasks include: 
  1. A C++ program to read text files containing the entries (rows) for each table, and build the database by creating each table and adding entries.
  2. A C++ library (set of functions) which will provide an interface for a program to interact with the database (e.g. add rows to the tables and query for certain information).

