static void find_mv_refs_idx ( const VP9_COMMON * cm , const MACROBLOCKD * xd , const TileInfo * const tile , MODE_INFO * mi , MV_REFERENCE_FRAME ref_frame , int_mv * mv_ref_list , int block , int mi_row , int mi_col ) {
 const int * ref_sign_bias = cm -> ref_frame_sign_bias ;
 int i , refmv_count = 0 ;
 const MODE_INFO * prev_mi = ! cm -> error_resilient_mode && cm -> prev_mi ? cm -> prev_mi [ mi_row * xd -> mi_stride + mi_col ] . src_mi : NULL ;
 const MB_MODE_INFO * const prev_mbmi = prev_mi ? & prev_mi -> src_mi -> mbmi : NULL ;
 const POSITION * const mv_ref_search = mv_ref_blocks [ mi -> mbmi . sb_type ] ;
 int different_ref_found = 0 ;
 int context_counter = 0 ;
 vpx_memset ( mv_ref_list , 0 , sizeof ( * mv_ref_list ) * MAX_MV_REF_CANDIDATES ) ;
 for ( i = 0 ;
 i < 2 ;
 ++ i ) {
 const POSITION * const mv_ref = & mv_ref_search [ i ] ;
 if ( is_inside ( tile , mi_col , mi_row , cm -> mi_rows , mv_ref ) ) {
 const MODE_INFO * const candidate_mi = xd -> mi [ mv_ref -> col + mv_ref -> row * xd -> mi_stride ] . src_mi ;
 const MB_MODE_INFO * const candidate = & candidate_mi -> mbmi ;
 context_counter += mode_2_counter [ candidate -> mode ] ;
 different_ref_found = 1 ;
 if ( candidate -> ref_frame [ 0 ] == ref_frame ) ADD_MV_REF_LIST ( get_sub_block_mv ( candidate_mi , 0 , mv_ref -> col , block ) ) ;
 else if ( candidate -> ref_frame [ 1 ] == ref_frame ) ADD_MV_REF_LIST ( get_sub_block_mv ( candidate_mi , 1 , mv_ref -> col , block ) ) ;
 }
 }
 for ( ;
 i < MVREF_NEIGHBOURS ;
 ++ i ) {
 const POSITION * const mv_ref = & mv_ref_search [ i ] ;
 if ( is_inside ( tile , mi_col , mi_row , cm -> mi_rows , mv_ref ) ) {
 const MB_MODE_INFO * const candidate = & xd -> mi [ mv_ref -> col + mv_ref -> row * xd -> mi_stride ] . src_mi -> mbmi ;
 different_ref_found = 1 ;
 if ( candidate -> ref_frame [ 0 ] == ref_frame ) ADD_MV_REF_LIST ( candidate -> mv [ 0 ] ) ;
 else if ( candidate -> ref_frame [ 1 ] == ref_frame ) ADD_MV_REF_LIST ( candidate -> mv [ 1 ] ) ;
 }
 }
 if ( prev_mbmi ) {
 if ( prev_mbmi -> ref_frame [ 0 ] == ref_frame ) ADD_MV_REF_LIST ( prev_mbmi -> mv [ 0 ] ) ;
 else if ( prev_mbmi -> ref_frame [ 1 ] == ref_frame ) ADD_MV_REF_LIST ( prev_mbmi -> mv [ 1 ] ) ;
 }
 if ( different_ref_found ) {
 for ( i = 0 ;
 i < MVREF_NEIGHBOURS ;
 ++ i ) {
 const POSITION * mv_ref = & mv_ref_search [ i ] ;
 if ( is_inside ( tile , mi_col , mi_row , cm -> mi_rows , mv_ref ) ) {
 const MB_MODE_INFO * const candidate = & xd -> mi [ mv_ref -> col + mv_ref -> row * xd -> mi_stride ] . src_mi -> mbmi ;
 IF_DIFF_REF_FRAME_ADD_MV ( candidate ) ;
 }
 }
 }
 if ( prev_mbmi ) IF_DIFF_REF_FRAME_ADD_MV ( prev_mbmi ) ;
 Done : mi -> mbmi . mode_context [ ref_frame ] = counter_to_context [ context_counter ] ;
 for ( i = 0 ;
 i < MAX_MV_REF_CANDIDATES ;
 ++ i ) clamp_mv_ref ( & mv_ref_list [ i ] . as_mv , xd ) ;
 }