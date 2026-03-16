static void encode_tiles ( VP9_COMP * cpi ) {
 const VP9_COMMON * const cm = & cpi -> common ;
 const int tile_cols = 1 << cm -> log2_tile_cols ;
 const int tile_rows = 1 << cm -> log2_tile_rows ;
 int tile_col , tile_row ;
 TOKENEXTRA * tok = cpi -> tok ;
 for ( tile_row = 0 ;
 tile_row < tile_rows ;
 ++ tile_row ) {
 for ( tile_col = 0 ;
 tile_col < tile_cols ;
 ++ tile_col ) {
 TileInfo tile ;
 TOKENEXTRA * old_tok = tok ;
 int mi_row ;
 vp9_tile_init ( & tile , cm , tile_row , tile_col ) ;
 for ( mi_row = tile . mi_row_start ;
 mi_row < tile . mi_row_end ;
 mi_row += MI_BLOCK_SIZE ) {
 if ( cpi -> sf . use_nonrd_pick_mode && ! frame_is_intra_only ( cm ) ) encode_nonrd_sb_row ( cpi , & tile , mi_row , & tok ) ;
 else encode_rd_sb_row ( cpi , & tile , mi_row , & tok ) ;
 }
 cpi -> tok_count [ tile_row ] [ tile_col ] = ( unsigned int ) ( tok - old_tok ) ;
 assert ( tok - cpi -> tok <= get_token_alloc ( cm -> mb_rows , cm -> mb_cols ) ) ;
 }
 }
 }