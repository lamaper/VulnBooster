static void set_arf_sign_bias ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 int arf_sign_bias ;
 if ( ( cpi -> oxcf . pass == 2 ) && cpi -> multi_arf_allowed ) {
 const GF_GROUP * const gf_group = & cpi -> twopass . gf_group ;
 arf_sign_bias = cpi -> rc . source_alt_ref_active && ( ! cpi -> refresh_alt_ref_frame || ( gf_group -> rf_level [ gf_group -> index ] == GF_ARF_LOW ) ) ;
 }
 else {
 arf_sign_bias = ( cpi -> rc . source_alt_ref_active && ! cpi -> refresh_alt_ref_frame ) ;
 }
 cm -> ref_frame_sign_bias [ ALTREF_FRAME ] = arf_sign_bias ;
 }