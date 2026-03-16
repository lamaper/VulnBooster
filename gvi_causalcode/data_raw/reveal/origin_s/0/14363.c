static void fill_mode_costs ( VP9_COMP * cpi ) {
 const FRAME_CONTEXT * const fc = & cpi -> common . fc ;
 int i , j ;
 for ( i = 0 ;
 i < INTRA_MODES ;
 ++ i ) for ( j = 0 ;
 j < INTRA_MODES ;
 ++ j ) vp9_cost_tokens ( cpi -> y_mode_costs [ i ] [ j ] , vp9_kf_y_mode_prob [ i ] [ j ] , vp9_intra_mode_tree ) ;
 vp9_cost_tokens ( cpi -> mbmode_cost , fc -> y_mode_prob [ 1 ] , vp9_intra_mode_tree ) ;
 vp9_cost_tokens ( cpi -> intra_uv_mode_cost [ KEY_FRAME ] , vp9_kf_uv_mode_prob [ TM_PRED ] , vp9_intra_mode_tree ) ;
 vp9_cost_tokens ( cpi -> intra_uv_mode_cost [ INTER_FRAME ] , fc -> uv_mode_prob [ TM_PRED ] , vp9_intra_mode_tree ) ;
 for ( i = 0 ;
 i < SWITCHABLE_FILTER_CONTEXTS ;
 ++ i ) vp9_cost_tokens ( cpi -> switchable_interp_costs [ i ] , fc -> switchable_interp_prob [ i ] , vp9_switchable_interp_tree ) ;
 }