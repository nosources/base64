//
//  base64.c
//  base64
//
//  Created by nosources on 14-9-30.
//  Copyright (c) 2014年 nosources. All rights reserved.
//

#include <stdio.h>
static const char encode_symbols[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
void encode_ss(char **plain_text, char *cipher_text){
    unsigned char to_encode[3];
    while (**plain_text != '\0') {
        //read 3 char to the to_encode.
        int i = 0;
        while (i < 3) {
            if ('\0' == (*(to_encode + i) = *(*plain_text)++)){
                (*plain_text)--;
                break;
            }
            i++;
        }
        *cipher_text++ = (unsigned char) encode_symbols[ (int)(to_encode[0] >> 2) ];
        *cipher_text++ = (unsigned char) encode_symbols[ (int)(((to_encode[0] & 0x03) << 4) | ((to_encode[1] & 0xf0) >> 4)) ];
        *cipher_text++ = (unsigned char) (i > 1 ? encode_symbols[ (int)(((to_encode[1] & 0x0f) << 2) | ((to_encode[2] & 0xc0) >> 6)) ] : '=');
        *cipher_text++ = (unsigned char) (i > 2 ? encode_symbols[ (int)(to_encode[2] & 0x3f) ] : '=');
	}
}

void decode_ss(char *cipher_text, char *plain_text){
    
}