#include "NRF24L01.h"

// =======================================================
// オブジェクト
// =======================================================
static RF24 m_NRFRadio( CE_PIN, CSN_PIN );

// =======================================================
// メンバ変数
// =======================================================
static const byte m_Address[ 6 ] = "NODE1";

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
    m_NRFRadio.openReadingPipe( 0, m_Address );
    m_NRFRadio.startListening( );
}

void NRF24_ReadMessage( bool *p_ButtonPushed )
{
    if ( m_NRFRadio.available( ) )
    {
        m_NRFRadio.read( p_ButtonPushed, sizeof( p_ButtonPushed ) );
    }
}