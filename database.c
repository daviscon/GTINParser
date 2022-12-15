//
//  database.c
//  
//
//  Created by Connor Davis on 25/6/21.
//

#include "database.h"
#include "main.h"

char*** createDatabase()
{
    /* Allocate memory for all pointers in database*/
    char*** database = (char***)malloc(ROW_LEN * sizeof(char**));
    for(int i = 0; i< ROW_LEN; i++)
    {
        database[i] = (char**)malloc(COL_LEN * sizeof(char*));
        for(int ii = 0; ii < COL_LEN; ii++)
        {
            database[i][ii] = (char*)calloc(STR_LEN, STR_LEN * sizeof(char));
        }
    }
    printf("--------------------\n| DATABASE CREATED |\n--------------------\n");
    return database;
}

void searchDatabase(char*** database, char* GS1, char* batch, FILE* writestream)
{
    char *SKU, *VIN, *MANU;
    char * check, *check2;
    int found = 0, count = 0;
    
    /* Parse through Database*/
    for(int i = 0; i < ROW_LEN; i++)
    {
        check = strdup(database[i][0]);
        /* Check for GS1 Match*/
        if(strcmp(check,GS1) == 0 && found == 0)
        {
            check2 = database[i][2];
            if(strcmp(batch, check2) == 0)
            {
                found = i;
            }
        }
    }
    
    /* Check Batch*/
    if(found == 0)
    {
        for(int i = 0; i < ROW_LEN; i++)
        {
            check = strdup(database[i][2]);
            /* Check for GS1 Match*/
            if(strcmp(check,batch) == 0)
            {
                count++;
                if(count == 1)
                {
                    found = i;
                }
                else
                {
                    found = 0;
                }
            }
        }
    }
    /* If not found allocate values to missing*/
    if(found == 0)
    {
        SKU = strdup("MISSING");
        VIN = strdup("MISSING");
        MANU = strdup("MISSING");
    }
    /* Else add values to result file*/
    else
    {
        SKU = strdup(database[found][1]);
        VIN = strdup(database[found][3]);
        MANU = strdup(database[found][4]);
    }
    
    /*Print values to file*/
    fprintf(writestream, ",%s,%s,%s\n",SKU, VIN, MANU);
}

void searchDatabase2(char*** database, char* SKU, char* batch, FILE* writestream)
{
    char *VIN, *MANU;
    char * check, *check2;
    int found = 0, count = 0;
    
    /* Parse through Database*/
    for(int i = 0; i < ROW_LEN; i++)
    {
        check = strdup(database[i][1]);
        /* Check for GS1 Match*/
        if(strcmp(check,SKU) == 0 && found == 0)
        {
            check2 = database[i][2];
            if(strcmp(batch, check2) == 0)
            {
                found = i;
            }
        }
    }
    
    /* Check Batch*/
    if(found == 0)
    {
        for(int i = 0; i < ROW_LEN; i++)
        {
            check = strdup(database[i][2]);
            /* Check for GS1 Match*/
            if(strcmp(check,batch) == 0)
            {
                count++;
                if(count == 1)
                {
                    found = i;
                }
                else
                {
                    found = 0;
                }
            }
        }
    }
    /* If not found allocate values to missing*/
    if(found == 0)
    {
        VIN = strdup("MISSING");
        MANU = strdup("MISSING");
    }
    /* Else add values to result file*/
    else
    {
        VIN = strdup(database[found][3]);
        MANU = strdup(database[found][4]);
    }
    
    /*Print values to file*/
    fprintf(writestream, ",%s,%s,%s\n",SKU, VIN, MANU);
}

void freeDatabase(char*** database)
{
    /* Free Database Pointers*/
    for(int i = 0; i < ROW_LEN; i++)
    {
        free(database[i]);
    }
    free(database);
    printf("------------------\n| DATABASE FREED |\n------------------\n");
}
