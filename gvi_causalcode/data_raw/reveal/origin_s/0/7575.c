static void update_coef_probs ( VP9_COMP * cpi , vp9_writer * w ) {
 const TX_MODE tx_mode = cpi -> common . tx_mode ;
 const TX_SIZE max_tx_size = tx_mode_to_biggest_tx_size [ tx_mode ] ;
 TX_SIZE tx_size ;
 vp9_coeff_stats frame_branch_ct [ TX_SIZES ] [ PLANE_TYPES ] ;
 vp9_coeff_probs_model frame_coef_probs [ TX_SIZES ] [ PLANE_TYPES ] ;
 for ( tx_size = TX_4X4 ;
 tx_size <= TX_32X32 ;
 ++ tx_size ) build_tree_distribution ( cpi , tx_size , frame_branch_ct [ tx_size ] , frame_coef_probs [ tx_size ] ) ;
 for ( tx_size = TX_4X4 ;
 tx_size <= max_tx_size ;
 ++ tx_size ) update_coef_probs_common ( w , cpi , tx_size , frame_branch_ct [ tx_size ] , frame_coef_probs [ tx_size ] ) ;
 }