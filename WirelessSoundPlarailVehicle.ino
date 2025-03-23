/**
 * =============================================================
 * @file        WirelessSoundPlarailVehicle.ino
 * @author      kinketsu patron (https://kinketsu-patron.com)
 * @brief       メインファイル
 * @version     1.0
 * @date        2025-02-09
 * =============================================================
 */

// =======================================================
// ヘッダインクルード
// =======================================================
#include "DFPlayer.h"
#include "NRF24L01.h"
#include <Arduino.h>

/**
 * =======================================================
 * @fn         setup
 * @brief      初期化を行う
 * @date       2025-02-10
 * =======================================================
 */
void setup( void )
{
    USB_Serial.begin( 9600 );  // USBデータ通信の通信速度
    while ( !USB_Serial )
    {
        // some boards need to wait to ensure access to serial over USB
    }
    pinMode( BUSY_PIN_NO, INPUT_PULLUP );
    Setup_DFPlayer( );
    Setup_NRF24( );
}

/**
 * =======================================================
 * @fn         loop
 * @brief      繰り返し処理を行う
 * @date       2025-02-10
 * =======================================================
 */
void loop( void )
{
    uint8_t w_PushedID;
    bool    w_IsRecv;

    delay( 50 );
    USB_Serial.println( "beforeReceived!" );
    w_IsRecv = NRF24_ReadMessage( &w_PushedID );
    USB_Serial.println( "Received!" );
    if ( w_IsRecv == true )
    {
        switch ( w_PushedID )
        {
            case PREV_ID:
                DFP_Prev( );
                break;
            case PLAY_ID:
                DFP_PlayPause( digitalRead( BUSY_PIN_NO ) );
                break;
            case NEXT_ID:
                DFP_Next( );
                break;
            case MODE_ID:
                DFP_ModeChange( );
                break;
            default: /* NONE */
                break;
        }
    }
    else
    {
        USB_Serial.println( "No Received." );
    }
    delay( 1000 );
    DFP_UpdatePlayStatus( digitalRead( BUSY_PIN_NO ) );
    NRF24_WriteMessage( DFP_GetPlayStatus( ), DFP_GetPlayTruckNo( ), DFP_GetPlayFolder( ) );
}