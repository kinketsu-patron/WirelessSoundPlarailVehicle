#include "NRF24L01.h"

// =======================================================
// オブジェクト
// =======================================================
static RF24 m_NRFRadio( CE_PIN_NO, CSN_PIN_NO );

// =======================================================
// メンバ変数
// =======================================================
static const byte m_ReceiveAddress[ 6 ] = "NODE1";
static const byte m_SendAddress[ 6 ]    = "NODE2";

/**
 * =======================================================
 * @fn          Setup_NRF24
 * @brief       初期化
 * @date        2025-02-13
 * =======================================================
 */
void Setup_NRF24( void )
{
    if ( m_NRFRadio.begin( ) == 0 )
    {
        USB_Serial.println( F( "radio hardware is not responding!!" ) );
        while ( true )
        {
            delay( 0 );
        }
    }

    m_NRFRadio.setPALevel( RF24_PA_MIN );
    m_NRFRadio.openWritingPipe( m_SendAddress );
    m_NRFRadio.openReadingPipe( 0, m_ReceiveAddress );
}

/**
 * =======================================================
 * @fn          NRF24_ReadMessage
 * @brief       無線でのメッセージ受信
 * @date        2025-02-13
 * =======================================================
 */
uint8_t NRF24_ReadMessage( void )
{
    uint8_t w_PushedID = 0U;

    m_NRFRadio.startListening( );

    while ( m_NRFRadio.available( ) )
    {
        m_NRFRadio.read( &w_PushedID, sizeof( w_PushedID ) );
    }
    return w_PushedID;
}

void NRF24_WriteMessage( )
{
    m_NRFRadio.stopListening( );
}