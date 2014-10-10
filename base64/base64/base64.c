//
//  base64.c
//  base64
//
//  Created by nosources on 14-9-30.
//  Copyright (c) 2014年 nosources. All rights reserved.
//

#include <stdio.h>
#include <string.h>
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
        *cipher_text++ = (unsigned char)encode_symbols[(int)(to_encode[0] >> 2)];
        *cipher_text++ = (unsigned char)encode_symbols[(int)(((to_encode[0] & 0x03) << 4) | ((to_encode[1] & 0xf0) >> 4))];
        *cipher_text++ = (unsigned char)(i > 1 ? encode_symbols[(int)(((to_encode[1] & 0x0f) << 2) | ((to_encode[2] & 0xc0) >> 6))] : '=');
        *cipher_text++ = (unsigned char)(i > 2 ? encode_symbols[(int)(to_encode[2] & 0x3f)] : '=');
	}
}
/*
A
01000001

Q      Q
010000 01
 */
//static const char decode_symbols[]="|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";
void decode_ss(char *cipher_text, char *plain_text){
    char *temp = plain_text;
    char decode_symbols[129] = {0};
    for (int i = 0; i < 128; i++) {
        decode_symbols[i] = '@';
    }
    for (int i = 0; i < sizeof(encode_symbols) - 1; i++) {
        unsigned char key = encode_symbols[i];
        unsigned char value = (unsigned char)i;
        int keyint = (int)key;
        decode_symbols[keyint] = value;
    }
    decode_symbols[(int)'='] = 0;
    unsigned char to_decode[4] = {0};
    while (*cipher_text) {
        //read 4 char to the to_decode.
        int i = 0;
        while (i < 4) {
            unsigned char temp = decode_symbols[*cipher_text++];
            *(to_decode + i) = (temp == '@' ? '\0' : temp);
            i++;
        }
        *plain_text++ = (unsigned char)(to_decode[0] << 2 | to_decode[1] >> 4);
        *plain_text++ = (unsigned char)(to_decode[1] << 4 | to_decode[2] >> 2);
        *plain_text++ = (unsigned char)(((to_decode[2] << 6) & 0xc0) | to_decode[3]);
        memset(&to_decode, '\0', sizeof(to_decode));
    }
}



















