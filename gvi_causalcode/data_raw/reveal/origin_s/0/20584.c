static void lsf2lsp_5 ( AMRContext * p ) {
 const uint16_t * lsf_param = p -> frame . lsf ;
 float lsf_no_r [ LP_FILTER_ORDER ] ;
 const int16_t * lsf_quantizer [ 5 ] ;
 int i ;
 lsf_quantizer [ 0 ] = lsf_5_1 [ lsf_param [ 0 ] ] ;
 lsf_quantizer [ 1 ] = lsf_5_2 [ lsf_param [ 1 ] ] ;
 lsf_quantizer [ 2 ] = lsf_5_3 [ lsf_param [ 2 ] >> 1 ] ;
 lsf_quantizer [ 3 ] = lsf_5_4 [ lsf_param [ 3 ] ] ;
 lsf_quantizer [ 4 ] = lsf_5_5 [ lsf_param [ 4 ] ] ;
 for ( i = 0 ;
 i < LP_FILTER_ORDER ;
 i ++ ) lsf_no_r [ i ] = p -> prev_lsf_r [ i ] * LSF_R_FAC * PRED_FAC_MODE_12k2 + lsf_5_mean [ i ] ;
 lsf2lsp_for_mode12k2 ( p , p -> lsp [ 1 ] , lsf_no_r , lsf_quantizer , 0 , lsf_param [ 2 ] & 1 , 0 ) ;
 lsf2lsp_for_mode12k2 ( p , p -> lsp [ 3 ] , lsf_no_r , lsf_quantizer , 2 , lsf_param [ 2 ] & 1 , 1 ) ;
 weighted_vector_sumd ( p -> lsp [ 0 ] , p -> prev_lsp_sub4 , p -> lsp [ 1 ] , 0.5 , 0.5 , LP_FILTER_ORDER ) ;
 weighted_vector_sumd ( p -> lsp [ 2 ] , p -> lsp [ 1 ] , p -> lsp [ 3 ] , 0.5 , 0.5 , LP_FILTER_ORDER ) ;
 }