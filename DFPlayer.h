#ifndef __DFPLAYER_H__
#define __DFPLAYER_H__

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "define.h"

void    Setup_DFPlayer( void );
void    DFP_PlayPause( PinStatus p_BusyLogic );
void    DFP_Next( void );
void    DFP_Prev( void );
void    DFP_ModeChange( void );
uint8_t DFP_GetPlayTruckNo( void );
uint8_t DFP_GetPlayFolder( void );
uint8_t DFP_GetPlayStatus( void );
void    DFP_UpdatePlayStatus( PinStatus p_BusyLogic );

#endif /* __DFPLAYER_H__ */