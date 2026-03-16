static void write_tile_info ( const VP9_COMMON * const cm , struct vp9_write_bit_buffer * wb ) {
 int min_log2_tile_cols , max_log2_tile_cols , ones ;
 vp9_get_tile_n_bits ( cm -> mi_cols , & min_log2_tile_cols , & max_log2_tile_cols ) ;
 ones = cm -> log2_tile_cols - min_log2_tile_cols ;
 while ( ones -- ) vp9_wb_write_bit ( wb , 1 ) ;
 if ( cm -> log2_tile_cols < max_log2_tile_cols ) vp9_wb_write_bit ( wb , 0 ) ;
 vp9_wb_write_bit ( wb , cm -> log2_tile_rows != 0 ) ;
 if ( cm -> log2_tile_rows != 0 ) vp9_wb_write_bit ( wb , cm -> log2_tile_rows != 1 ) ;
 }