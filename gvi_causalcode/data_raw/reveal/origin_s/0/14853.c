static void set_tile_limits ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 int min_log2_tile_cols , max_log2_tile_cols ;
 vp9_get_tile_n_bits ( cm -> mi_cols , & min_log2_tile_cols , & max_log2_tile_cols ) ;
 cm -> log2_tile_cols = clamp ( cpi -> oxcf . tile_columns , min_log2_tile_cols , max_log2_tile_cols ) ;
 cm -> log2_tile_rows = cpi -> oxcf . tile_rows ;
 }