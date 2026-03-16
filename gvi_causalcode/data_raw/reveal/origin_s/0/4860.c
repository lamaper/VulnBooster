static void MPV_encode_defaults ( MpegEncContext * s ) {
 int i ;
 ff_MPV_common_defaults ( s ) ;
 for ( i = - 16 ;
 i < 16 ;
 i ++ ) {
 default_fcode_tab [ i + MAX_MV ] = 1 ;
 }
 s -> me . mv_penalty = default_mv_penalty ;
 s -> fcode_tab = default_fcode_tab ;
 }