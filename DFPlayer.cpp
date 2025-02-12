#include "DFPlayer.h"

// =======================================================
// オブジェクト
// =======================================================
static DFRobotDFPlayerMini m_DFPlayer;

// =======================================================
// ローカル変数
// =======================================================
static uint8_t m_PlayFolder;
static bool    m_HasModeChanged;

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

    m_DFPlayer.volume( 30 );  // 0～30中の30に設定
    m_PlayFolder     = 1U;
    m_HasModeChanged = false;
}

void PlayPause( void )
{
    if ( m_HasModeChanged == true )
    {
        m_DFPlayer.playFolder( m_PlayFolder, 1U );
    }
    else
    {
        switch ( m_DFPlayer.readState( ) )
        {
        case 513U: /* 再生中 */
            m_DFPlayer.pause( );
            break;
        case 514: /* ポーズ中 */
            m_DFPlayer.play( );
            break;
        default:
            break;
        }
    }
}

void Next( void )
{
    m_DFPlayer.next( );
}

void Prev( void )
{
    m_DFPlayer.previous( );
}

void ModeChange( void )
{
    m_HasModeChanged = true;

    if ( m_PlayFolder == 1U )
    {
        m_PlayFolder = 2U;
    }
    else if ( m_PlayFolder == 2U )
    {
        m_PlayFolder = 99U;
    }
    else
    {
        m_PlayFolder = 1U;
    }
}