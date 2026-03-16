static int rv34_decode_block ( int16_t * dst , GetBitContext * gb , RV34VLC * rvlc , int fc , int sc , int q_dc , int q_ac1 , int q_ac2 ) {
 int code , pattern , has_ac = 1 ;
 code = get_vlc2 ( gb , rvlc -> first_pattern [ fc ] . table , 9 , 2 ) ;
 pattern = code & 0x7 ;
 code >>= 3 ;
 if ( modulo_three_table [ code ] & 0x3F ) {
 decode_subblock3 ( dst , code , gb , & rvlc -> coefficient , q_dc , q_ac1 , q_ac2 ) ;
 }
 else {
 decode_subblock1 ( dst , code , gb , & rvlc -> coefficient , q_dc ) ;
 if ( ! pattern ) return 0 ;
 has_ac = 0 ;
 }
 if ( pattern & 4 ) {
 code = get_vlc2 ( gb , rvlc -> second_pattern [ sc ] . table , 9 , 2 ) ;
 decode_subblock ( dst + 4 * 0 + 2 , code , 0 , gb , & rvlc -> coefficient , q_ac2 ) ;
 }
 if ( pattern & 2 ) {
 code = get_vlc2 ( gb , rvlc -> second_pattern [ sc ] . table , 9 , 2 ) ;
 decode_subblock ( dst + 4 * 2 + 0 , code , 1 , gb , & rvlc -> coefficient , q_ac2 ) ;
 }
 if ( pattern & 1 ) {
 code = get_vlc2 ( gb , rvlc -> third_pattern [ sc ] . table , 9 , 2 ) ;
 decode_subblock ( dst + 4 * 2 + 2 , code , 0 , gb , & rvlc -> coefficient , q_ac2 ) ;
 }
 return has_ac | pattern ;
 }