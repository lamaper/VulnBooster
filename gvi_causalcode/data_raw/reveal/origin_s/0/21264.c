static size_t encode_tiles ( VP9_COMP * cpi , uint8_t * data_ptr ) {
 VP9_COMMON * const cm = & cpi -> common ;
 vp9_writer residual_bc ;
 int tile_row , tile_col ;
 TOKENEXTRA * tok [ 4 ] [ 1 << 6 ] , * tok_end ;
 size_t total_size = 0 ;
 const int tile_cols = 1 << cm -> log2_tile_cols ;
 const int tile_rows = 1 << cm -> log2_tile_rows ;
 vpx_memset ( cm -> above_seg_context , 0 , sizeof ( * cm -> above_seg_context ) * mi_cols_aligned_to_sb ( cm -> mi_cols ) ) ;
 tok [ 0 ] [ 0 ] = cpi -> tok ;
 for ( tile_row = 0 ;
 tile_row < tile_rows ;
 tile_row ++ ) {
 if ( tile_row ) tok [ tile_row ] [ 0 ] = tok [ tile_row - 1 ] [ tile_cols - 1 ] + cpi -> tok_count [ tile_row - 1 ] [ tile_cols - 1 ] ;
 for ( tile_col = 1 ;
 tile_col < tile_cols ;
 tile_col ++ ) tok [ tile_row ] [ tile_col ] = tok [ tile_row ] [ tile_col - 1 ] + cpi -> tok_count [ tile_row ] [ tile_col - 1 ] ;
 }
 for ( tile_row = 0 ;
 tile_row < tile_rows ;
 tile_row ++ ) {
 for ( tile_col = 0 ;
 tile_col < tile_cols ;
 tile_col ++ ) {
 TileInfo tile ;
 vp9_tile_init ( & tile , cm , tile_row , tile_col ) ;
 tok_end = tok [ tile_row ] [ tile_col ] + cpi -> tok_count [ tile_row ] [ tile_col ] ;
 if ( tile_col < tile_cols - 1 || tile_row < tile_rows - 1 ) vp9_start_encode ( & residual_bc , data_ptr + total_size + 4 ) ;
 else vp9_start_encode ( & residual_bc , data_ptr + total_size ) ;
 write_modes ( cpi , & tile , & residual_bc , & tok [ tile_row ] [ tile_col ] , tok_end ) ;
 assert ( tok [ tile_row ] [ tile_col ] == tok_end ) ;
 vp9_stop_encode ( & residual_bc ) ;
 if ( tile_col < tile_cols - 1 || tile_row < tile_rows - 1 ) {
 mem_put_be32 ( data_ptr + total_size , residual_bc . pos ) ;
 total_size += 4 ;
 }
 total_size += residual_bc . pos ;
 }
 }
 return total_size ;
 }