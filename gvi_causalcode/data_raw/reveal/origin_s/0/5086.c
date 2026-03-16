static int8_t getNextDynamicWindow ( SCSUData * scsu ) {
 int8_t window = scsu -> windowUse [ scsu -> nextWindowUseIndex ] ;
 if ( ++ scsu -> nextWindowUseIndex == 8 ) {
 scsu -> nextWindowUseIndex = 0 ;
 }
 return window ;
 }