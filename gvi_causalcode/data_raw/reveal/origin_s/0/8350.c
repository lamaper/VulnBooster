static void init_uni_h263_rl_tab ( RLTable * rl , uint32_t * bits_tab , uint8_t * len_tab ) {
 int slevel , run , last ;
 assert ( MAX_LEVEL >= 64 ) ;
 assert ( MAX_RUN >= 63 ) ;
 for ( slevel = - 64 ;
 slevel < 64 ;
 slevel ++ ) {
 if ( slevel == 0 ) continue ;
 for ( run = 0 ;
 run < 64 ;
 run ++ ) {
 for ( last = 0 ;
 last <= 1 ;
 last ++ ) {
 const int index = UNI_MPEG4_ENC_INDEX ( last , run , slevel + 64 ) ;
 int level = slevel < 0 ? - slevel : slevel ;
 int sign = slevel < 0 ? 1 : 0 ;
 int bits , len , code ;
 len_tab [ index ] = 100 ;
 code = get_rl_index ( rl , last , run , level ) ;
 bits = rl -> table_vlc [ code ] [ 0 ] ;
 len = rl -> table_vlc [ code ] [ 1 ] ;
 bits = bits * 2 + sign ;
 len ++ ;
 if ( code != rl -> n && len < len_tab [ index ] ) {
 if ( bits_tab ) bits_tab [ index ] = bits ;
 len_tab [ index ] = len ;
 }
 bits = rl -> table_vlc [ rl -> n ] [ 0 ] ;
 len = rl -> table_vlc [ rl -> n ] [ 1 ] ;
 bits = bits * 2 + last ;
 len ++ ;
 bits = bits * 64 + run ;
 len += 6 ;
 bits = bits * 256 + ( level & 0xff ) ;
 len += 8 ;
 if ( len < len_tab [ index ] ) {
 if ( bits_tab ) bits_tab [ index ] = bits ;
 len_tab [ index ] = len ;
 }
 }
 }
 }
 }