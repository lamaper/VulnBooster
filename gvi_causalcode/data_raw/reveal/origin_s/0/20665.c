static int apply_cyclic_refresh_bitrate ( const VP9_COMMON * cm , const RATE_CONTROL * rc ) {
 const float factor = 0.5 ;
 const int number_blocks = cm -> mi_rows * cm -> mi_cols ;
 if ( rc -> avg_frame_bandwidth < factor * number_blocks || number_blocks / 64 < 5 ) return 0 ;
 else return 1 ;
 }