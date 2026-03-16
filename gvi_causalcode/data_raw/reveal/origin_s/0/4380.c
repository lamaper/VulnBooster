void vp9_save_layer_context ( VP9_COMP * const cpi ) {
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 LAYER_CONTEXT * const lc = get_layer_context ( cpi ) ;
 lc -> rc = cpi -> rc ;
 lc -> twopass = cpi -> twopass ;
 lc -> target_bandwidth = ( int ) oxcf -> target_bandwidth ;
 lc -> alt_ref_source = cpi -> alt_ref_source ;
 }