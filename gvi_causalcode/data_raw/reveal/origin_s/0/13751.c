static unsigned int get_joining_type ( hb_codepoint_t u , hb_unicode_general_category_t gen_cat ) {
 unsigned int j_type = joining_type ( u ) ;
 if ( likely ( j_type != JOINING_TYPE_X ) ) return j_type ;
 return ( FLAG_SAFE ( gen_cat ) & ( FLAG ( HB_UNICODE_GENERAL_CATEGORY_NON_SPACING_MARK ) | FLAG ( HB_UNICODE_GENERAL_CATEGORY_ENCLOSING_MARK ) | FLAG ( HB_UNICODE_GENERAL_CATEGORY_FORMAT ) ) ) ? JOINING_TYPE_T : JOINING_TYPE_U ;
 }