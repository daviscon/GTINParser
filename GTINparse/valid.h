//
//  valid.h
//  
//
//  Created by Connor Davis on 30/6/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STR_LEN 64

char* valGTIN(char* GTIN);

char* valSSCC(char* SSCC);

char* valBatch(char* batch);

char* valQTY(char* QTY);

char* valBin(char* bin);

char* validate(char* field, int code);

char* subString(char *s, int a, int b);
