#ifndef _TEA_H_
#define _TEA_H_

#include <stdint.h>

/*
buf must have enough space,align 8 bytes
*/
extern uint32_t tea_string_encrypt(uint8_t *buf,uint32_t len,uint8_t *key);
extern uint32_t tea_string_decrypt(uint8_t *buf,uint32_t len,uint8_t *key);


#endif //_TEA_H_
