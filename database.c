#include "database.h"

// Create a new database
Database *create_db(char *name)
{
    Database *db = (Database *)malloc(sizeof(Database));
    db->DB_NAME = malloc(strlen(name) + 1);
    strcpy(db->DB_NAME, name);
    db->tables = NULL;
    db->tables_count = 0;
    return db;
}

// Insert data into the table if it exists, otherwise create a new table and insert the data
void insert(Database *db, char *table_name, char *data)
{
    for (int i = 0; i < db->tables_count; i++)
    {
        if (strcmp(db->tables[i].name, table_name) == 0)
        {
            Table *table = &(db->tables[i]);
            table->rows = realloc(table->rows, sizeof(Row) * (table->rows_count + 1));
            if (table->rows != NULL)
            {
                table->rows_count++;
                Row *row = &(table->rows[table->rows_count - 1]);
                row->id = table->CURR_ID;
                table->CURR_ID++;
                row->data = malloc(strlen(data) + 1);
                if (row->data != NULL)
                {
                    strcpy(row->data, data);
                    printf("Data Entered into the row\n");
                    return;
                }
                printf("Error in allocationg memory for the row->data.\n");
                return;
            }
            printf("Error in inserting the data.\n");
            return;
        }
    }
    db->tables_count++;
    db->tables = realloc(db->tables, sizeof(Table) * db->tables_count);
    if (db->tables != NULL)
    {
        Table *table = &(db->tables[db->tables_count - 1]);
        table->CURR_ID = 0;
        table->name = malloc(strlen(table_name) + 1);
        if (table->name != NULL)
        {
            strcpy(table->name, table_name);
            table->rows = NULL;
            table->rows_count = 0;
            insert(db, table_name, data);
            return;
        }
        printf("Error in allocating memory for the table->name.\n");
        return;
    }
    printf("Error in inserting the data.\n");
    return;
}

void update(Database *db, char *table_name, int id, char *new_data)
{
    for (int i = 0; i < db->tables_count; i++)
    {
        if (strcmp(db->tables[i].name, table_name) == 0)
        {
            Table *table = &(db->tables[i]);
            for (int j = 0; j < table->rows_count; j++)
            {
                Row *row = &(table->rows[j]);
                if (row->id == id)
                {
                    // Free the old data
                    free(row->data);
                    // Allocate memory for the new data
                    row->data = malloc(strlen(new_data) + 1);
                    if (row->data != NULL)
                    {
                        strcpy(row->data, new_data);
                        printf("Data Updated.\n");
                        return;
                    }
                    printf("Error in allocating memory for the row->data.\n");
                    return;
                }
            }
            printf("Row not found.\n");
            return;
        }
    }
    printf("Table not found.\n");
}

void print_table(Database *db, char *table_name)
{
    for (int i = 0; i < db->tables_count; i++)
    {
        if (strcmp(db->tables[i].name, table_name) == 0)
        {
            Table *table = &(db->tables[i]);
            printf("Table Name: %s\n", table->name);
            printf("Rows Count: %d\n", table->rows_count);

            for (int j = 0; j < table->rows_count; j++)
            {
                Row *row = &(table->rows[j]);
                printf("Row ID: %d, Data: %s\n", row->id, row->data);
            }

            printf("\n");
            return;
        }
    }
    printf("Table not found.\n");
}

// Cleanup the database
void cleanup(Database *db)
{
    free(db->DB_NAME);
    for (int i = 0; i < db->tables_count; i++)
    {
        Table *table = &(db->tables[i]);
        free(table->name);

        for (int j = 0; j < table->rows_count; j++)
        {
            Row *row = &(table->rows[j]);
            free(row->data);
        }

        free(table->rows);
    }

    free(db->tables);
    free(db);
}