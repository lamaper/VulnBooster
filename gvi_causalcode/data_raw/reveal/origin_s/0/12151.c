static void save_coding_context ( VP9_COMP * cpi ) {
 CODING_CONTEXT * const cc = & cpi -> coding_context ;
 VP9_COMMON * cm = & cpi -> common ;
 vp9_copy ( cc -> nmvjointcost , cpi -> mb . nmvjointcost ) ;
 vpx_memcpy ( cc -> nmvcosts [ 0 ] , cpi -> nmvcosts [ 0 ] , MV_VALS * sizeof ( * cpi -> nmvcosts [ 0 ] ) ) ;
 vpx_memcpy ( cc -> nmvcosts [ 1 ] , cpi -> nmvcosts [ 1 ] , MV_VALS * sizeof ( * cpi -> nmvcosts [ 1 ] ) ) ;
 vpx_memcpy ( cc -> nmvcosts_hp [ 0 ] , cpi -> nmvcosts_hp [ 0 ] , MV_VALS * sizeof ( * cpi -> nmvcosts_hp [ 0 ] ) ) ;
 vpx_memcpy ( cc -> nmvcosts_hp [ 1 ] , cpi -> nmvcosts_hp [ 1 ] , MV_VALS * sizeof ( * cpi -> nmvcosts_hp [ 1 ] ) ) ;
 vp9_copy ( cc -> segment_pred_probs , cm -> seg . pred_probs ) ;
 vpx_memcpy ( cpi -> coding_context . last_frame_seg_map_copy , cm -> last_frame_seg_map , ( cm -> mi_rows * cm -> mi_cols ) ) ;
 vp9_copy ( cc -> last_ref_lf_deltas , cm -> lf . last_ref_deltas ) ;
 vp9_copy ( cc -> last_mode_lf_deltas , cm -> lf . last_mode_deltas ) ;
 cc -> fc = cm -> fc ;
 }