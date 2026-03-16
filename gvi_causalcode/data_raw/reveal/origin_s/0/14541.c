static int16_t read_table ( ChannelData * chd , uint8_t val , int tab_idx ) {
 int16_t current ;
 if ( val < tabs [ tab_idx ] . stride ) current = tabs [ tab_idx ] . tab2 [ ( ( chd -> index & 0x7f0 ) >> 4 ) * tabs [ tab_idx ] . stride + val ] ;
 else current = - 1 - tabs [ tab_idx ] . tab2 [ ( ( chd -> index & 0x7f0 ) >> 4 ) * tabs [ tab_idx ] . stride + 2 * tabs [ tab_idx ] . stride - val - 1 ] ;
 if ( ( chd -> index += tabs [ tab_idx ] . tab1 [ val ] - ( chd -> index >> 5 ) ) < 0 ) chd -> index = 0 ;
 return current ;
 }