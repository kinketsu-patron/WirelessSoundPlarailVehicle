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

/**
 * =======================================================
 * @fn         setup
 * @brief      初期化を行う
 * @date       2025-02-10
 * =======================================================
 */
void setup( void )
{
    pinMode( BUSY_PIN_NO, INPUT );
    Setup_DFPlayer( );
    Setup_NRF24( );
    USB_Serial.begin( 115200 );  // USBデータ通信の通信速度
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
    static uint8_t w_PushedID;

    w_PushedID = NRF24_ReadMessage( );

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
        default:
            break;
    }
    delay( 50 );
}