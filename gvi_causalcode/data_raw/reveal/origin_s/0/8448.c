static void decode_block ( VP9_COMMON * const cm , MACROBLOCKD * const xd , const TileInfo * const tile , int mi_row , int mi_col , vp9_reader * r , BLOCK_SIZE bsize ) {
 const int less8x8 = bsize < BLOCK_8X8 ;
 MB_MODE_INFO * mbmi = set_offsets ( cm , xd , tile , bsize , mi_row , mi_col ) ;
 vp9_read_mode_info ( cm , xd , tile , mi_row , mi_col , r ) ;
 if ( less8x8 ) bsize = BLOCK_8X8 ;
 if ( mbmi -> skip ) {
 reset_skip_context ( xd , bsize ) ;
 }
 else {
 if ( cm -> seg . enabled ) setup_plane_dequants ( cm , xd , vp9_get_qindex ( & cm -> seg , mbmi -> segment_id , cm -> base_qindex ) ) ;
 }
 if ( ! is_inter_block ( mbmi ) ) {
 struct intra_args arg = {
 cm , xd , r }
 ;
 vp9_foreach_transformed_block ( xd , bsize , predict_and_reconstruct_intra_block , & arg ) ;
 }
 else {
 set_ref ( cm , xd , 0 , mi_row , mi_col ) ;
 if ( has_second_ref ( mbmi ) ) set_ref ( cm , xd , 1 , mi_row , mi_col ) ;
 vp9_dec_build_inter_predictors_sb ( xd , mi_row , mi_col , bsize ) ;
 if ( ! mbmi -> skip ) {
 int eobtotal = 0 ;
 struct inter_args arg = {
 cm , xd , r , & eobtotal }
 ;
 vp9_foreach_transformed_block ( xd , bsize , reconstruct_inter_block , & arg ) ;
 if ( ! less8x8 && eobtotal == 0 ) mbmi -> skip = 1 ;
 }
 }
 xd -> corrupted |= vp9_reader_has_error ( r ) ;
 }