static void restore_coding_context ( VP9_COMP * cpi ) {
 CODING_CONTEXT * const cc = & cpi -> coding_context ;
 VP9_COMMON * cm = & cpi -> common ;
 vp9_copy ( cpi -> mb . nmvjointcost , cc -> nmvjointcost ) ;
 vpx_memcpy ( cpi -> nmvcosts [ 0 ] , cc -> nmvcosts [ 0 ] , MV_VALS * sizeof ( * cc -> nmvcosts [ 0 ] ) ) ;
 vpx_memcpy ( cpi -> nmvcosts [ 1 ] , cc -> nmvcosts [ 1 ] , MV_VALS * sizeof ( * cc -> nmvcosts [ 1 ] ) ) ;
 vpx_memcpy ( cpi -> nmvcosts_hp [ 0 ] , cc -> nmvcosts_hp [ 0 ] , MV_VALS * sizeof ( * cc -> nmvcosts_hp [ 0 ] ) ) ;
 vpx_memcpy ( cpi -> nmvcosts_hp [ 1 ] , cc -> nmvcosts_hp [ 1 ] , MV_VALS * sizeof ( * cc -> nmvcosts_hp [ 1 ] ) ) ;
 vp9_copy ( cm -> seg . pred_probs , cc -> segment_pred_probs ) ;
 vpx_memcpy ( cm -> last_frame_seg_map , cpi -> coding_context . last_frame_seg_map_copy , ( cm -> mi_rows * cm -> mi_cols ) ) ;
 vp9_copy ( cm -> lf . last_ref_deltas , cc -> last_ref_lf_deltas ) ;
 vp9_copy ( cm -> lf . last_mode_deltas , cc -> last_mode_lf_deltas ) ;
 cm -> fc = cc -> fc ;
 }