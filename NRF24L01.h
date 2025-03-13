#ifndef __NRF24_H__
#define __NRF24_H__

#include "Arduino.h"
#include "RF24.h"
#include "define.h"
#include "nRF24L01.h"
#include <SPI.h>


struct SoundData
{
    uint8_t PlayStatus;
    uint8_t TruckNo;
    uint8_t PlayFolder;
};

void    Setup_NRF24( void );
uint8_t NRF24_ReadMessage( void );
void    NRF24_WriteMessage( uint8_t p_PlayStatus, uint8_t p_TruckNo, uint8_t p_PlayFolder );

#endif /* NRF24_H */