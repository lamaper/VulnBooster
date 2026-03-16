static uint8_t get_filter_level ( const loop_filter_info_n * lfi_n , const MB_MODE_INFO * mbmi ) {
 return lfi_n -> lvl [ mbmi -> segment_id ] [ mbmi -> ref_frame [ 0 ] ] [ mode_lf_lut [ mbmi -> mode ] ] ;
 }