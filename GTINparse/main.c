/*
//  main.c
//  GTINparse
//
//  Created by Connor Davis on 24/6/21.
*/

#include "main.h"


int main(int argc, const char * argv[])
{
    FILE *palletstream, *singlestream, *writestream, *filestream;
    char line[1024];
    char *SSCC, *GS1, *buffer, *buffer2;
    char *GTIN = NULL, *BATCH = NULL, *QTY = NULL, *BIN = NULL, *SKU = NULL;
    int i = 0, ii = 0, digits = 0, count, progress = 0;
    unsigned long length = 0;
    char*** database = NULL;
    int row = 0, column = 0;

    printf("GTIN Parsing Commencing...\nPlease Ensure your Input File are named \"PALLET.csv\" & \"SINGLE.csv\"\n");
    printf("And your Database File is named \"Database.csv\"\nResults will be saved to file \"RESULTFILE.csv\"\n");
    
    /* Clearing Result File*/
    writestream = fopen("RESULTFILE.csv", "w");
    fclose(writestream);
    
    /* Opening File Streams */
    singlestream = fopen("SINGLE.csv", "r");
    palletstream = fopen("PALLET.csv", "r");
    writestream = fopen("RESULTFILE.csv", "a");
    filestream = fopen("DATABASE.csv", "r");
    
    /*Testing Files for Error*/
    if (!filestream || !singlestream || !palletstream)
    {
        printf("Can't find Files\n");
    }

    /* Creating & Filling Database */
    database = createDatabase(database);
    
    /* Allocating new buffer*/
    buffer2 = (char*)malloc(256 * sizeof(char));
    printf("DATABASE FILL PROGRESS:");
    /* Parsing through database file and allocating to 3D array*/
    while(fgets(buffer2, 256, filestream))
    {
        progress = ((progress + 1) % (ROW_LEN/25));
        database[row][0] = strtok(buffer2, ", ");
        for(column = 1; column < COL_LEN; column++)
        {
            database[row][column] = strtok(NULL, ", ");
        }
        row++;
        buffer2 = (char*)malloc(256 * sizeof(char));
        if(progress == ((ROW_LEN/25)-1))
        {
            printf("█");
            usleep(100000);
        }
        
    }
    printf("\n");
    /* Free buffer & Close Database File stream*/
    free(buffer2);
    fclose(filestream);
    printf("-------------------\n| DATABASE FILLED |\n-------------------\n");
    
    /* Writing column values*/
    fprintf(writestream, "SSCC,GS1,Qty,Batch,Bin,Item,Vintage,DOM\n");
    
    printf("STOCKTAKE PROCESS COMMENCING\n");
    while (fgets(line, 1024, palletstream))
    {
        /* Initialising values*/
        count = 0;
        digits = 3;
        i = 0;
        ii = 0;
        
        /* Parse SSCC */
        buffer = strtok(line, ",");
        SSCC = strdup(buffer);
        length = strlen(SSCC);
        /* Cutting off quotation marks*/
        //SSCC = substr(SSCC, 1, (int)(length-2));
        SSCC = valSSCC(SSCC);
        /* Parse GS1*/
        buffer = strtok(NULL, ",");
        GS1 = strdup(buffer);
        
        /* Parse Quantity*/
        buffer = strtok(NULL, ",");
        QTY = strdup(buffer);
        
        /* Parse Bin Location*/
        buffer = strtok(NULL, ",");
        BIN = strdup(buffer);
        length = strlen(BIN);
        
        /* Clipping newline char*/
        BIN = substr(BIN, 0, (int)(length-2));
        BIN = valBin(BIN);
        
        /* Parsing GS1 from GTIN*/
        GTIN = substr(GS1, 3, 13);
        GTIN = valGTIN(GTIN);
        
        /* Checking if Manufacture Date is included*/
        if(GS1[16] == '1')
        {
            i = 8;
        }
        /* Checking if QTY is 4 digits*/
        if(GS1[22 + i] == '1' && (GS1[23 + i] == '1' || GS1[23 + i] == '5' || GS1[23 + i] == '0'))
        {
            digits = 4;
        }
        
        if(GS1[20 + i] == '1' && (GS1[21 + i] == '1' || GS1[21 + i] == '5'|| GS1[21 + i] == '0'))
        {
            digits = 2;
        }
        
        /* Parsing Quantity from GS1*/
        if(strcmp(QTY, "0") == 0)
        {
            QTY = substr(GS1, (18 + i), digits);
        }
        QTY = valQTY(QTY);
        
        if(GS1[19 + digits + i] == '1' || GS1[19 + digits + i] == '5')
        {
            ii = 8;
        }
         
        /* Finding digit length of Batch*/
        count = (int)(strlen(GS1) - (20 + i + digits + ii));
        
        /* Parsing Batch*/
        BATCH = substr(GS1, (20 + digits + i + ii), (count));
        if(BATCH[0] == '1' && BATCH[1] == '0')
        {
            BATCH = substr(BATCH, 2, (count-2));
            QTY = strcat(QTY,"FLAG");
        }
        BATCH = valBatch(BATCH);
        
        /* Writes values to csv file*/
        fprintf(writestream, "%s,%s,%s,%s,%s",SSCC, GTIN, QTY, BATCH, BIN);
        /* Searching for GTIN in Database and saving results*/
        searchDatabase(database, GTIN, BATCH, writestream);
        
    }
          
    while (fgets(line, 1024, singlestream))
    {
        buffer = strtok(line, ",");
        SSCC = strdup(buffer);
        length = strlen(SSCC);
        /* Cutting off quotation marks*/
        //SSCC = substr(SSCC, 1, (int)(length-2));
        SSCC = valSSCC(SSCC);
        
        GTIN = "EMPTY";
        
        /* Parse Sku*/
        buffer = strtok(NULL, ",");
        SKU = strdup(buffer);
        
        /* Parse Quantity*/
        buffer = strtok(NULL, ",");
        QTY = strdup(buffer);
        QTY = valQTY(QTY);
        
        /* Parse BATCH*/
        buffer = strtok(NULL, ",");
        BATCH = strdup(buffer);
        BATCH = valBatch(BATCH);
        
        /* Parse Bin Location*/
        buffer = strtok(NULL, ",");
        BIN = strdup(buffer);
        length = strlen(BIN);
        
        /* Clipping newline char*/
        BIN = substr(BIN, 0, (int)(length-2));
        BIN = valBin(BIN);
        
        fprintf(writestream, "%s,%s,%s,%s,%s",SSCC, GTIN, QTY, BATCH, BIN);
        
        searchDatabase2(database, SKU, BATCH, writestream);
        
    }
    
    printf("----------------\n| FILE CREATED |\n----------------\n");
    
    /* File Cleanup*/
    fclose(palletstream);
    fclose(writestream);
    free(QTY);free(BATCH);
    
    freeDatabase(database);
    
    printf("--------------------------\n| COMPLETED SUCCESSFULLY |\n--------------------------\n");
     
    return 0;
}

/*FUNCTION:substr
  DESC: Finds the substring of original string betweeen two bounds
  IMPORT: Original String, Start Length, End Length
  EXPORT: Sub String within bounds of original string
 */
char* substr(char *s, int a, int b)
{
    char* t = (char*)malloc(STR_LEN * sizeof(char));
    strncpy(t, s+a, b);
    
    return t;
}
