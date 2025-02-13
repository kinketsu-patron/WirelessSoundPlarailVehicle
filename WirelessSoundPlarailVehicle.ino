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
    USB_Serial.begin( 115200 );  // USBデータ通信の通信速度
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
    static bool w_ButtonPushed[ 4 ];

    NRF24_ReadMessage( w_ButtonPushed );

    if ( w_ButtonPushed[ 0 ] == true )
    {
        DFP_Prev( );
    }
    if ( w_ButtonPushed[ 1 ] == true )
    {
        DFP_PlayPause( );
    }
    if ( w_ButtonPushed[ 2 ] == true )
    {
        DFP_Next( );
    }
    if ( w_ButtonPushed[ 3 ] == true )
    {
        DFP_ModeChange( );
    }
    delay( 100 );
}