/*
 * Copyright (c) 2014 Zhao, Gang <gang.zhao.42@gmail.com>
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 */

#include <string.h>
#include "common.h"
#include "crypto.h"
#include "tea.h"

int iv_len;
//static const EVP_CIPHER *evp_cipher;
//static const EVP_MD *md;
static const uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
//static uint8_t key[MAX_KEY_LENGTH];
static uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
static unsigned  int key_len;

#define  ALIGN_8(size)  (((size) % 8) ? ((size) + (8 - ((size) % 8))) : (size))

int get_method(char *password, char *method)
{	
	int len = strlen(password);
	if( len > 16)
		memcpy(key,password,16);
	else
		memcpy(key,password,len);
	
	return 0;
}

int crypto_init(char *password, char *method)
{
	if (get_method(password, method) == -1)
		return -1;

	iv_len = sizeof(iv);
	
	return 0;
}

void crypto_exit(void)
{

}

int crypto_encrypt(int sockfd, struct link *ln)
{
	ln->cipher_len = tea_string_encrypt(ln->text,ln->text_len,key);
	memcpy(ln->cipher,ln->text,ln->cipher_len);

	/* encryption succeeded, so text buffer is not needed */
	ln->text_len = 0;

	return ln->cipher_len;
}

int crypto_decrypt(int sockfd, struct link *ln)
{
	ln->text_len = tea_string_decrypt(ln->cipher,ln->cipher_len,key);
	memcpy(ln->text,ln->cipher,ln->text_len);
	
	/* decryption succeeded, so cipher buffer is not needed */
	ln->cipher_len = 0;

	return ln->text_len;
}
