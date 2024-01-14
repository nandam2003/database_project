#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

int main()
{
    // Createing a new database
    Database *myDatabase = create_db("MyDatabase");

    // Insert data into tables
    insert(myDatabase, "Table1", "Data1");
    insert(myDatabase, "Table2", "Data2");
    insert(myDatabase, "Table1", "Data3");
    insert(myDatabase, "Table1", "Data4");
    insert(myDatabase, "Table2", "Data5");

    // Print the database content
    print_table(myDatabase, "Table1");
    print_table(myDatabase, "Table2");

    update(myDatabase, "Table1", 2, "New Data");

    cleanup(myDatabase);
    printf("Database cleaned up.\n");

    return 0;
}
