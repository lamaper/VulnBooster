static void setup_tile_info ( VP9_COMMON * cm , struct vp9_read_bit_buffer * rb ) {
 int min_log2_tile_cols , max_log2_tile_cols , max_ones ;
 vp9_get_tile_n_bits ( cm -> mi_cols , & min_log2_tile_cols , & max_log2_tile_cols ) ;
 max_ones = max_log2_tile_cols - min_log2_tile_cols ;
 cm -> log2_tile_cols = min_log2_tile_cols ;
 while ( max_ones -- && vp9_rb_read_bit ( rb ) ) cm -> log2_tile_cols ++ ;
 if ( cm -> log2_tile_cols > 6 ) vpx_internal_error ( & cm -> error , VPX_CODEC_CORRUPT_FRAME , "Invalid number of tile columns" ) ;
 cm -> log2_tile_rows = vp9_rb_read_bit ( rb ) ;
 if ( cm -> log2_tile_rows ) cm -> log2_tile_rows += vp9_rb_read_bit ( rb ) ;
 }