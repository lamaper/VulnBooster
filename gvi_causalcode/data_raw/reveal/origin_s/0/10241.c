MV clamp_mv_to_umv_border_sb ( const MACROBLOCKD * xd , const MV * src_mv , int bw , int bh , int ss_x , int ss_y ) {
 const int spel_left = ( VP9_INTERP_EXTEND + bw ) << SUBPEL_BITS ;
 const int spel_right = spel_left - SUBPEL_SHIFTS ;
 const int spel_top = ( VP9_INTERP_EXTEND + bh ) << SUBPEL_BITS ;
 const int spel_bottom = spel_top - SUBPEL_SHIFTS ;
 MV clamped_mv = {
 src_mv -> row * ( 1 << ( 1 - ss_y ) ) , src_mv -> col * ( 1 << ( 1 - ss_x ) ) }
 ;
 assert ( ss_x <= 1 ) ;
 assert ( ss_y <= 1 ) ;
 clamp_mv ( & clamped_mv , xd -> mb_to_left_edge * ( 1 << ( 1 - ss_x ) ) - spel_left , xd -> mb_to_right_edge * ( 1 << ( 1 - ss_x ) ) + spel_right , xd -> mb_to_top_edge * ( 1 << ( 1 - ss_y ) ) - spel_top , xd -> mb_to_bottom_edge * ( 1 << ( 1 - ss_y ) ) + spel_bottom ) ;
 return clamped_mv ;
 }