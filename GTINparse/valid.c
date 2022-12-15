//
//  valid.c
//  
//
//  Created by Connor Davis on 30/6/21.
//

#include "valid.h"

char* valSSCC(char* SSCC)
{
    char* result = SSCC;
    unsigned long length = strlen(result);
    
    if(result[0] == '0')
    {
        result = validate(result,1);
    }
    if(result[0] == '0' && result[1] != '9')
    {
        result = validate(result,1);
    }
    if(length != 18)
    {
        if(result[length-1] != '0')
        {
            result = validate(result,2);
        }
    }
    if(result[1] != '9' || result[2] != '3')
    {
        result = validate(result,3);
    }

    return result;
}

char* valGTIN(char* GTIN)
{
    char* result = GTIN;
    unsigned long length = strlen(result);
    
    if(GTIN[0] != '9' && GTIN[0] != '0')
    {
        result = validate(result,6);
    }
    if(length != 13)
    {
        if(result[length-1] != '0')
        {
            result = validate(result,7);
        }
    }
    
    return result;
}

char* valBatch(char* batch)
{
    char* result = batch;
    /*unsigned long length = strlen(result);
    
    if(length < 5 || length > 11)
    {
        result = validate(result,9);
    }
    if(result[length-1] == 'V')
    {
        result = validate(result,10);
    }
    if(result[0] != '1' && result [0] != '2')
    {
        result = validate(result,11);
    }*/
    
    return result;
}

char* valQTY(char* QTY)
{
    char* result = QTY;
    int number = atoi(result);
    int length = 0;

    if(result[0] == '0')
    {
        result = validate(result, 14);
    }
    if(result[0] == '0')
    {
        result = validate(result, 14);
    }
    if(number < 0 || number > 128)
    {
        result = validate(result, 12);
    }
    while(isdigit(result[length]))
    {
        length++;
    }
    if(length < 1 || length > 3)
    {
        
        result = validate(result, 13);
    }
    
    return (char*)result;
}

char* valBin(char* bin)
{
    //char bound1, bound2;
    char* result = bin;
    unsigned long length = strlen(result);
    /* TO BE FIXED*/
    if((int)length != 3 && (int)length != 4 && (int) length != 5)
    {
        if(result[length-1] != '0')
        {
            result = validate(result,2);
        }
    }
    /*bound1 = result[0]; bound2 = 'L';
    if(strcmp(result, "REC1") != 0 ||strcmp(result, "PAD1") != 0 || bound1 >= bound2)
    {
        result = validate(result,22);
    }
    if(result[0] >= 'A' && result[0] <= 'E' && result[0] != 'C')
    {
        if(atoi(subString(result, 1,(int)length)) > 44)
        {
            result = validate(result,23);
        }
    }
    if(result[0] == 'C')
    {
        if(result[1] > 'J')
        {
            result = validate(result,23);
        }
        else
        {
            if(atoi(subString(result, 2,(int)length)) > 44)
            {
                result = validate(result,23);
            }
        }
    }
    if(result[0] >= 'L')
    {
        result = validate(result,23);
    }
    else
    {
        if(result[0] >= 'F' && (atoi(subString(result, 1,(int)length)) > 22))
        {
            result = validate(result,23);
        }
    }*/

    return result;
}


char* validate(char* field, int code)
{
    char* result = field;
    unsigned long length = strlen(result);
    

    switch(code)
    {
        case 1:
            result = subString(result,1,(int)length);
            break;
            
        case 2:
            printf("SSCC - Wrong Digit Length\nSSCC:%s Length:%d\n\n", field, (int)length);

            break;
            
        case 3:
            printf("SSCC - Wrong Prefix\nSSCC:%s\n\n", field);


            break;
            
        case 6:
            printf("GTIN - Wrong Prefix\nGTIN:%s\n\n", field);


            break;
        
        case 7:
            printf("GTIN - Wrong Digit Length\nGTIN:%s Length:%d\n\n", field, (int)length);


            break;
            
        case 9:
            printf("Batch - Wrong Digit Length \nBatch:%s Length:%d\n\n", field, (int)length);


            break;
            
        case 10:
            printf("Batch - Contains Letter \nBatch:%s\n\n", field);


            break;
            
        case 11:
            printf("Batch - Wrong Prefix \nBatch:%s\n\n", field);

            
            break;
            
        case 12:
            printf("Quantity - Outside Bounds \nQTY:%s\n\n", field);


            break;
            
        case 13:
            printf("Quantity - Wrong Digit Length \nQTY:%s Length:%d\n\n", field, (int)length);


            break;
        
        case 14:
            result = subString(result,1,(int)length);
            break;
            
        case 21:
            printf("Bin Location  - Wrong Digit Length \nBin:%s Length:%d\n\n", field, (int)length);


            break;
            
        case 22:
            printf("Bin Location  - Wrong Entry \nBin:%s\n\n", field);


            break;
            
        case 23:
            printf("Bin Location  - Out of Bounds \nBin:%s\n\n", field);


            break;
    }
    
    return result;
}

char* subString(char *s, int a, int b)
{
    char* t = (char*)malloc(STR_LEN * sizeof(char));
    strncpy(t, s+a, b);
    
    return t;
}
