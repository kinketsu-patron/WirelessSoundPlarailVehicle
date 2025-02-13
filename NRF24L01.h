#ifndef __NRF24_H__
#define __NRF24_H__

#include "Arduino.h"
#include "RF24.h"
#include "define.h"

void    Setup_NRF24( void );
uint8_t NRF24_ReadMessage( void );

#endif /* NRF24_H */