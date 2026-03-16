static void write_modes_b ( VP9_COMP * cpi , const TileInfo * const tile , vp9_writer * w , TOKENEXTRA * * tok , const TOKENEXTRA * const tok_end , int mi_row , int mi_col ) {
 const VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCKD * const xd = & cpi -> mb . e_mbd ;
 MODE_INFO * m ;
 xd -> mi = cm -> mi_grid_visible + ( mi_row * cm -> mi_stride + mi_col ) ;
 m = xd -> mi [ 0 ] ;
 set_mi_row_col ( xd , tile , mi_row , num_8x8_blocks_high_lookup [ m -> mbmi . sb_type ] , mi_col , num_8x8_blocks_wide_lookup [ m -> mbmi . sb_type ] , cm -> mi_rows , cm -> mi_cols ) ;
 if ( frame_is_intra_only ( cm ) ) {
 write_mb_modes_kf ( cm , xd , xd -> mi , w ) ;
 }
 else {
 pack_inter_mode_mvs ( cpi , m , w ) ;
 }
 assert ( * tok < tok_end ) ;
 pack_mb_tokens ( w , tok , tok_end ) ;
 }