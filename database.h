//
//  database.h
//  
//
//  Created by Connor Davis on 25/6/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_LEN 1375
#define COL_LEN 5
#define STR_LEN 64
#define ENTRY_LEN 13

char*** createDatabase(char*** database);

void searchDatabase(char*** database, char* GS1, char* batch, FILE* writestream);

void searchDatabase2(char*** database, char* SKU, char* batch, FILE* writestream);

void freeDatabase(char*** database);
