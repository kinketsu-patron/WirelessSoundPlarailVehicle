#ifndef __NRF24_H__
#define __NRF24_H__

#include "Arduino.h"
#include "RF24.h"
#include "define.h"

typedef struct
{
    uint8_t PushedID;
    uint8_t TruckNo;
    uint8_t PlayFolder;
    uint8_t PinStatus;
} MSG;

void    Setup_NRF24( void );
uint8_t NRF24_ReadMessage( void );
void    NRF24_WriteMessage( uint8_t p_PushedID, uint8_t p_TruckNo, uint8_t p_PlayFolder, uint8_t p_PinStatus );

#endif /* NRF24_H */