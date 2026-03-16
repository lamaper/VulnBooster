static MV_REFERENCE_FRAME get_frame_type ( const VP9_COMP * cpi ) {
 if ( frame_is_intra_only ( & cpi -> common ) ) return INTRA_FRAME ;
 else if ( cpi -> rc . is_src_frame_alt_ref && cpi -> refresh_golden_frame ) return ALTREF_FRAME ;
 else if ( cpi -> refresh_golden_frame || cpi -> refresh_alt_ref_frame ) return GOLDEN_FRAME ;
 else return LAST_FRAME ;
 }