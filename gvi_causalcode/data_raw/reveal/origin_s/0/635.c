static inline void x8_select_ac_table ( IntraX8Context * const w , int mode ) {
 MpegEncContext * const s = w -> s ;
 int table_index ;
 assert ( mode < 4 ) ;
 if ( w -> j_ac_vlc [ mode ] ) return ;
 table_index = get_bits ( & s -> gb , 3 ) ;
 w -> j_ac_vlc [ mode ] = & j_ac_vlc [ w -> quant < 13 ] [ mode >> 1 ] [ table_index ] ;
 assert ( w -> j_ac_vlc [ mode ] ) ;
 }