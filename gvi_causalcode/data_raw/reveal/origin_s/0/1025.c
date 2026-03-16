static indic_position_t consonant_position_from_face ( const indic_shape_plan_t * indic_plan , const hb_codepoint_t consonant , const hb_codepoint_t virama , hb_face_t * face ) {
 hb_codepoint_t glyphs [ 3 ] = {
 virama , consonant , virama }
 ;
 if ( indic_plan -> blwf . would_substitute ( glyphs , 2 , face ) || indic_plan -> blwf . would_substitute ( glyphs + 1 , 2 , face ) ) return POS_BELOW_C ;
 if ( indic_plan -> pstf . would_substitute ( glyphs , 2 , face ) || indic_plan -> pstf . would_substitute ( glyphs + 1 , 2 , face ) ) return POS_POST_C ;
 unsigned int pref_len = indic_plan -> config -> pref_len ;
 if ( ( pref_len == PREF_LEN_2 && ( indic_plan -> pref . would_substitute ( glyphs , 2 , face ) || indic_plan -> pref . would_substitute ( glyphs + 1 , 2 , face ) ) ) || ( pref_len == PREF_LEN_1 && indic_plan -> pref . would_substitute ( glyphs + 1 , 1 , face ) ) ) return POS_POST_C ;
 return POS_BASE_C ;
 }