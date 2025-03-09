#include "NRF24L01.h"

// =======================================================
// オブジェクト
// =======================================================
static RF24 m_NRFRadio( CE_PIN_NO, CSN_PIN_NO );

const byte m_Address_ToTrain[ 6 ]      = "TOTRN";
const byte m_Address_ToController[ 6 ] = "TOCTL";

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
    m_NRFRadio.openWritingPipe( m_Address_ToController );
    m_NRFRadio.openReadingPipe( 0, m_Address_ToTrain );
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
    uint8_t w_PushedID = NONE;

    m_NRFRadio.startListening( );

    while ( m_NRFRadio.available( ) )
    {
        m_NRFRadio.read( &w_PushedID, sizeof( w_PushedID ) );
    }
    return w_PushedID;
}

void NRF24_WriteMessage( uint8_t p_PlayStatus, uint8_t p_TruckNo, uint8_t p_PlayFolder )
{
    MSG w_Message;

    m_NRFRadio.stopListening( );
    w_Message.PlayStatus = p_PlayStatus;
    w_Message.TruckNo    = p_TruckNo;
    w_Message.PlayFolder = p_PlayFolder;
    m_NRFRadio.write( &w_Message, sizeof( w_Message ) );
}