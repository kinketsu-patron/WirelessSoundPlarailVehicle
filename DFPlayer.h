#ifndef __DFPLAYER_H__
#define __DFPLAYER_H__

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "define.h"

void Setup_DFPlayer( void );
void PlayPause( void );
void Next( void );
void Prev( void );
void ModeChange( void );

#endif /* __DFPLAYER_H__ */