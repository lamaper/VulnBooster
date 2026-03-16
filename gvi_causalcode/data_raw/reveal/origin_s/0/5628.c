static int frame_is_boosted ( const VP9_COMP * cpi ) {
 return frame_is_intra_only ( & cpi -> common ) || cpi -> refresh_alt_ref_frame || ( cpi -> refresh_golden_frame && ! cpi -> rc . is_src_frame_alt_ref ) || vp9_is_upper_layer_key_frame ( cpi ) ;
 }