static int get_zbin_mode_boost ( const MB_MODE_INFO * mbmi , int enabled ) {
 if ( enabled ) {
 if ( is_inter_block ( mbmi ) ) {
 if ( mbmi -> mode == ZEROMV ) {
 return mbmi -> ref_frame [ 0 ] != LAST_FRAME ? GF_ZEROMV_ZBIN_BOOST : LF_ZEROMV_ZBIN_BOOST ;
 }
 else {
 return mbmi -> sb_type < BLOCK_8X8 ? SPLIT_MV_ZBIN_BOOST : MV_ZBIN_BOOST ;
 }
 }
 else {
 return INTRA_ZBIN_BOOST ;
 }
 }
 else {
 return 0 ;
 }
 }