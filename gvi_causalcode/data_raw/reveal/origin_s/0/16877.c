static void read_ref_frames ( VP9_COMMON * const cm , MACROBLOCKD * const xd , vp9_reader * r , int segment_id , MV_REFERENCE_FRAME ref_frame [ 2 ] ) {
 FRAME_CONTEXT * const fc = & cm -> fc ;
 FRAME_COUNTS * const counts = & cm -> counts ;
 if ( vp9_segfeature_active ( & cm -> seg , segment_id , SEG_LVL_REF_FRAME ) ) {
 ref_frame [ 0 ] = ( MV_REFERENCE_FRAME ) vp9_get_segdata ( & cm -> seg , segment_id , SEG_LVL_REF_FRAME ) ;
 ref_frame [ 1 ] = NONE ;
 }
 else {
 const REFERENCE_MODE mode = read_block_reference_mode ( cm , xd , r ) ;
 if ( mode == COMPOUND_REFERENCE ) {
 const int idx = cm -> ref_frame_sign_bias [ cm -> comp_fixed_ref ] ;
 const int ctx = vp9_get_pred_context_comp_ref_p ( cm , xd ) ;
 const int bit = vp9_read ( r , fc -> comp_ref_prob [ ctx ] ) ;
 if ( ! cm -> frame_parallel_decoding_mode ) ++ counts -> comp_ref [ ctx ] [ bit ] ;
 ref_frame [ idx ] = cm -> comp_fixed_ref ;
 ref_frame [ ! idx ] = cm -> comp_var_ref [ bit ] ;
 }
 else if ( mode == SINGLE_REFERENCE ) {
 const int ctx0 = vp9_get_pred_context_single_ref_p1 ( xd ) ;
 const int bit0 = vp9_read ( r , fc -> single_ref_prob [ ctx0 ] [ 0 ] ) ;
 if ( ! cm -> frame_parallel_decoding_mode ) ++ counts -> single_ref [ ctx0 ] [ 0 ] [ bit0 ] ;
 if ( bit0 ) {
 const int ctx1 = vp9_get_pred_context_single_ref_p2 ( xd ) ;
 const int bit1 = vp9_read ( r , fc -> single_ref_prob [ ctx1 ] [ 1 ] ) ;
 if ( ! cm -> frame_parallel_decoding_mode ) ++ counts -> single_ref [ ctx1 ] [ 1 ] [ bit1 ] ;
 ref_frame [ 0 ] = bit1 ? ALTREF_FRAME : GOLDEN_FRAME ;
 }
 else {
 ref_frame [ 0 ] = LAST_FRAME ;
 }
 ref_frame [ 1 ] = NONE ;
 }
 else {
 assert ( 0 && "Invalid prediction mode." ) ;
 }
 }
 }