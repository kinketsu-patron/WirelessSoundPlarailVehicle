#include "DFPlayer.h"

// =======================================================
// オブジェクト
// =======================================================
static DFRobotDFPlayerMini m_DFPlayer;

// =======================================================
// ローカル変数
// =======================================================
static uint8_t m_PlayFolder;
static uint8_t m_PlayNumber;
static uint8_t m_FileCount[ 3 ] = { 21U, 47U, 3U };

/**
 * =======================================================
 * @fn         Setup_DFPlayer
 * @brief      DFPlayerの初期化を行う
 * @date       2025-02-11
 * =======================================================
 */
void Setup_DFPlayer( void )
{
    DF_Serial.begin( 9600 );  // DFPlayer miniとの通信速度(仕様制約)

    // 2秒以内に初期化できなかった場合はエラーメッセージが表示される
    if ( m_DFPlayer.begin( DF_Serial, /*isACK = */ true, /*doReset = */ true ) == 0 )
    {
        USB_Serial.println( F( "Unable to begin:" ) );
        USB_Serial.println( F( "1.Please recheck the connection!" ) );
        USB_Serial.println( F( "2.Please insert the SD card!" ) );

        // 無限ループに入れてウォッチドッグでリセットをかける
        while ( true )
        {
            delay( 0 );  // Code to compatible with ESP8266 watch dog.
        }
    }
    USB_Serial.println( F( "DFPlayer Mini online." ) );

    m_DFPlayer.volume( 5 );  // 0～30中の30に設定
    m_PlayFolder = 1U;
    m_PlayNumber = 1U;
}

void DFP_PlayPause( PinStatus p_BusyLogic )
{
    if ( p_BusyLogic == HIGH ) /* 現在再生停止中 */
    {
        m_DFPlayer.playFolder( m_PlayFolder, m_PlayNumber );
        USB_Serial.print( m_PlayFolder );
        USB_Serial.print( ", " );
        USB_Serial.print( m_PlayNumber );
        USB_Serial.println( " Play!" );
    }
    else /* 現在再生中 */
    {
        m_DFPlayer.pause( );
        USB_Serial.println( " Stop!" );
    }
}

void DFP_Next( void )
{
    m_PlayNumber++;
    if ( m_PlayNumber > m_FileCount[ m_PlayFolder - 1U ] )
    {
        m_PlayNumber = 1U;
    }
    m_DFPlayer.playFolder( m_PlayFolder, m_PlayNumber );

    USB_Serial.print( m_PlayFolder );
    USB_Serial.print( ", " );
    USB_Serial.print( m_PlayNumber );
    USB_Serial.println( " Play!" );
}

void DFP_Prev( void )
{
    m_PlayNumber--;
    if ( m_PlayNumber < 1U )
    {
        m_PlayNumber = m_FileCount[ m_PlayFolder - 1U ];
    }
    m_DFPlayer.playFolder( m_PlayFolder, m_PlayNumber );

    USB_Serial.print( m_PlayFolder );
    USB_Serial.print( ", " );
    USB_Serial.print( m_PlayNumber );
    USB_Serial.println( " Play!" );
}

void DFP_ModeChange( void )
{
    if ( m_PlayFolder == 1U )
    {
        m_PlayFolder = 2U;
    }
    else if ( m_PlayFolder == 2U )
    {
        m_PlayFolder = 3U;
    }
    else
    {
        m_PlayFolder = 1U;
    }
    m_PlayNumber = 1U;

    USB_Serial.print( "Mode = " );
    USB_Serial.println( m_PlayFolder );
}