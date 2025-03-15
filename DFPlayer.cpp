#include "DFPlayer.h"

// =======================================================
// オブジェクト
// =======================================================
static DFRobotDFPlayerMini m_DFPlayer;

// =======================================================
// ローカル変数
// =======================================================
static uint8_t m_PlayFolder;
static uint8_t m_PlayTruckNo;
static uint8_t m_PlayStatus;
static uint8_t m_FileCount[ 2 ] = { 21U, 20U };

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
    m_PlayFolder  = 1U;
    m_PlayTruckNo = 1U;
    m_PlayStatus  = STOP;
}

void DFP_PlayPause( PinStatus p_BusyLogic )
{
    if ( p_BusyLogic == HIGH ) /* 現在再生停止中 */
    {
        m_PlayStatus = IN_PLAY;
        m_DFPlayer.playFolder( m_PlayFolder, m_PlayTruckNo );
        USB_Serial.print( m_PlayFolder );
        USB_Serial.print( ", " );
        USB_Serial.print( m_PlayTruckNo );
        USB_Serial.println( " Play!" );
    }
    else /* 現在再生中 */
    {
        m_PlayStatus = STOP;
        m_DFPlayer.stop( );
        USB_Serial.println( " Stop!" );
    }
}

void DFP_Next( void )
{
    m_PlayTruckNo++;
    if ( m_PlayTruckNo > m_FileCount[ m_PlayFolder - 1U ] )
    {
        m_PlayTruckNo = 1U;
    }
    m_PlayStatus = IN_NEXT;
    m_DFPlayer.playFolder( m_PlayFolder, m_PlayTruckNo );

    USB_Serial.print( m_PlayFolder );
    USB_Serial.print( ", " );
    USB_Serial.print( m_PlayTruckNo );
    USB_Serial.println( " Play!" );
}

void DFP_Prev( void )
{
    m_PlayTruckNo--;
    if ( m_PlayTruckNo < 1U )
    {
        m_PlayTruckNo = m_FileCount[ m_PlayFolder - 1U ];
    }
    m_PlayStatus = IN_PREV;
    m_DFPlayer.playFolder( m_PlayFolder, m_PlayTruckNo );

    USB_Serial.print( m_PlayFolder );
    USB_Serial.print( ", " );
    USB_Serial.print( m_PlayTruckNo );
    USB_Serial.println( " Play!" );
}

void DFP_ModeChange( void )
{
    if ( m_PlayFolder == 1U )
    {
        m_PlayFolder = 2U;
    }
    else
    {
        m_PlayFolder = 1U;
    }
    m_PlayTruckNo = 1U;

    USB_Serial.print( "Mode = " );
    USB_Serial.println( m_PlayFolder );
}

uint8_t DFP_GetPlayTruckNo( void )
{
    return m_PlayTruckNo;
}

uint8_t DFP_GetPlayFolder( void )
{
    return m_PlayFolder;
}

uint8_t DFP_GetPlayStatus( void )
{
    return m_PlayStatus;
}

void DFP_UpdatePlayStatus( PinStatus p_BusyLogic )
{
    if ( p_BusyLogic == HIGH )
    {
        m_PlayStatus = STOP;
    }
}