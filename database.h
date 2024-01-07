// database.h

#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char *data;
} Row;

typedef struct
{
    int CURR_ID;
    char *name;
    Row *rows;
    int rows_count;
} Table;

typedef struct
{
    char *DB_NAME;
    Table *tables;
    int tables_count;
} Database;

// Function prototypes
Database *create_db(char *name);
void insert(Database *db, char *table_name, char *data);
void print_table(Database *db, char *table_name);
void cleanup(Database *db);

#endif // DATABASE_H