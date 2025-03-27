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
    m_NRFRadio.setPALevel( RF24_PA_LOW );
    m_NRFRadio.setPayloadSize( 3U /* bytes */ );
    m_NRFRadio.setRetries( 15, 15 );
    m_NRFRadio.openWritingPipe( m_Address_ToController );
    m_NRFRadio.openReadingPipe( 1, m_Address_ToTrain );
}

/**
 * =======================================================
 * @fn          NRF24_ReadMessage
 * @brief       無線でのメッセージ受信
 * @date        2025-02-13
 * =======================================================
 */
bool NRF24_ReadMessage( uint8_t *p_PushedID )
{
    uint8_t w_Pipe;
    uint8_t w_Bytes;
    bool    w_Result = false;

    *p_PushedID = NONE;
    m_NRFRadio.startListening( );
    while ( m_NRFRadio.available( &w_Pipe ) )
    {
        w_Bytes = m_NRFRadio.getPayloadSize( );  // get the size of the payload
        m_NRFRadio.read( p_PushedID, sizeof( uint8_t ) );
        USB_Serial.print( F( "Received " ) );
        USB_Serial.print( w_Bytes );  // print the size of the payload
        USB_Serial.print( F( " bytes on pipe " ) );
        USB_Serial.println( w_Pipe );  // print the pipe number
        w_Result = true;
    }
    return w_Result;
}

void NRF24_WriteMessage( uint8_t p_PlayStatus, uint8_t p_TruckNo, uint8_t p_PlayFolder )
{
    uint32_t  w_StartTimer, w_EndTimer;
    SOUNDDATA w_Message;
    bool      w_Report = false;

    m_NRFRadio.stopListening( );
    w_Message.PlayStatus = p_PlayStatus;
    w_Message.TruckNo    = p_TruckNo;
    w_Message.PlayFolder = p_PlayFolder;
    w_StartTimer         = micros( );
    w_Report             = m_NRFRadio.write( &w_Message, sizeof( SOUNDDATA ) );
    w_EndTimer           = micros( );

    if ( w_Report )
    {
        USB_Serial.print( F( "Transmission successful! " ) );  // payload was delivered
        USB_Serial.print( F( "Time to transmit = " ) );
        USB_Serial.print( w_EndTimer - w_StartTimer );  // print the timer result
        USB_Serial.println( F( " us. Sent: " ) );
        USB_Serial.print( "PlayStatus = " );
        USB_Serial.print( w_Message.PlayStatus );
        USB_Serial.print( ", TruckNo = " );
        USB_Serial.print( w_Message.TruckNo );
        USB_Serial.print( ", PlayFolder = " );
        USB_Serial.println( w_Message.PlayFolder );
    }
    else
    {
        USB_Serial.println( "Can't send Message." );
    }
}