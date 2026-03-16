static void chomp6 ( ChannelData * chd , int16_t * output , uint8_t val , int tab_idx ) {
 int16_t current = read_table ( chd , val , tab_idx ) ;
 if ( ( chd -> previous ^ current ) >= 0 ) {
 chd -> factor = FFMIN ( chd -> factor + 506 , 32767 ) ;
 }
 else {
 if ( chd -> factor - 314 < - 32768 ) chd -> factor = - 32767 ;
 else chd -> factor -= 314 ;
 }
 current = mace_broken_clip_int16 ( current + chd -> level ) ;
 chd -> level = ( current * chd -> factor ) >> 15 ;
 current >>= 1 ;
 output [ 0 ] = QT_8S_2_16S ( chd -> previous + chd -> prev2 - ( ( chd -> prev2 - current ) >> 2 ) ) ;
 output [ 1 ] = QT_8S_2_16S ( chd -> previous + current + ( ( chd -> prev2 - current ) >> 2 ) ) ;
 chd -> prev2 = chd -> previous ;
 chd -> previous = current ;
 }