static void write_modes ( VP9_COMP * cpi , const TileInfo * const tile , vp9_writer * w , TOKENEXTRA * * tok , const TOKENEXTRA * const tok_end ) {
 int mi_row , mi_col ;
 for ( mi_row = tile -> mi_row_start ;
 mi_row < tile -> mi_row_end ;
 mi_row += MI_BLOCK_SIZE ) {
 vp9_zero ( cpi -> mb . e_mbd . left_seg_context ) ;
 for ( mi_col = tile -> mi_col_start ;
 mi_col < tile -> mi_col_end ;
 mi_col += MI_BLOCK_SIZE ) write_modes_sb ( cpi , tile , w , tok , tok_end , mi_row , mi_col , BLOCK_64X64 ) ;
 }
 }