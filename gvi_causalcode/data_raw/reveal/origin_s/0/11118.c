static void estimate_ref_frame_costs ( const VP9_COMMON * cm , const MACROBLOCKD * xd , int segment_id , unsigned int * ref_costs_single , unsigned int * ref_costs_comp , vp9_prob * comp_mode_p ) {
 int seg_ref_active = vp9_segfeature_active ( & cm -> seg , segment_id , SEG_LVL_REF_FRAME ) ;
 if ( seg_ref_active ) {
 vpx_memset ( ref_costs_single , 0 , MAX_REF_FRAMES * sizeof ( * ref_costs_single ) ) ;
 vpx_memset ( ref_costs_comp , 0 , MAX_REF_FRAMES * sizeof ( * ref_costs_comp ) ) ;
 * comp_mode_p = 128 ;
 }
 else {
 vp9_prob intra_inter_p = vp9_get_intra_inter_prob ( cm , xd ) ;
 vp9_prob comp_inter_p = 128 ;
 if ( cm -> reference_mode == REFERENCE_MODE_SELECT ) {
 comp_inter_p = vp9_get_reference_mode_prob ( cm , xd ) ;
 * comp_mode_p = comp_inter_p ;
 }
 else {
 * comp_mode_p = 128 ;
 }
 ref_costs_single [ INTRA_FRAME ] = vp9_cost_bit ( intra_inter_p , 0 ) ;
 if ( cm -> reference_mode != COMPOUND_REFERENCE ) {
 vp9_prob ref_single_p1 = vp9_get_pred_prob_single_ref_p1 ( cm , xd ) ;
 vp9_prob ref_single_p2 = vp9_get_pred_prob_single_ref_p2 ( cm , xd ) ;
 unsigned int base_cost = vp9_cost_bit ( intra_inter_p , 1 ) ;
 if ( cm -> reference_mode == REFERENCE_MODE_SELECT ) base_cost += vp9_cost_bit ( comp_inter_p , 0 ) ;
 ref_costs_single [ LAST_FRAME ] = ref_costs_single [ GOLDEN_FRAME ] = ref_costs_single [ ALTREF_FRAME ] = base_cost ;
 ref_costs_single [ LAST_FRAME ] += vp9_cost_bit ( ref_single_p1 , 0 ) ;
 ref_costs_single [ GOLDEN_FRAME ] += vp9_cost_bit ( ref_single_p1 , 1 ) ;
 ref_costs_single [ ALTREF_FRAME ] += vp9_cost_bit ( ref_single_p1 , 1 ) ;
 ref_costs_single [ GOLDEN_FRAME ] += vp9_cost_bit ( ref_single_p2 , 0 ) ;
 ref_costs_single [ ALTREF_FRAME ] += vp9_cost_bit ( ref_single_p2 , 1 ) ;
 }
 else {
 ref_costs_single [ LAST_FRAME ] = 512 ;
 ref_costs_single [ GOLDEN_FRAME ] = 512 ;
 ref_costs_single [ ALTREF_FRAME ] = 512 ;
 }
 if ( cm -> reference_mode != SINGLE_REFERENCE ) {
 vp9_prob ref_comp_p = vp9_get_pred_prob_comp_ref_p ( cm , xd ) ;
 unsigned int base_cost = vp9_cost_bit ( intra_inter_p , 1 ) ;
 if ( cm -> reference_mode == REFERENCE_MODE_SELECT ) base_cost += vp9_cost_bit ( comp_inter_p , 1 ) ;
 ref_costs_comp [ LAST_FRAME ] = base_cost + vp9_cost_bit ( ref_comp_p , 0 ) ;
 ref_costs_comp [ GOLDEN_FRAME ] = base_cost + vp9_cost_bit ( ref_comp_p , 1 ) ;
 }
 else {
 ref_costs_comp [ LAST_FRAME ] = 512 ;
 ref_costs_comp [ GOLDEN_FRAME ] = 512 ;
 }
 }
 }