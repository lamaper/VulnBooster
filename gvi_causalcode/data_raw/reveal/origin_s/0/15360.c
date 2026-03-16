static void useDynamicWindow ( SCSUData * scsu , int8_t window ) {
 int i , j ;
 i = scsu -> nextWindowUseIndex ;
 do {
 if ( -- i < 0 ) {
 i = 7 ;
 }
 }
 while ( scsu -> windowUse [ i ] != window ) ;
 j = i + 1 ;
 if ( j == 8 ) {
 j = 0 ;
 }
 while ( j != scsu -> nextWindowUseIndex ) {
 scsu -> windowUse [ i ] = scsu -> windowUse [ j ] ;
 i = j ;
 if ( ++ j == 8 ) {
 j = 0 ;
 }
 }
 scsu -> windowUse [ i ] = window ;
 }