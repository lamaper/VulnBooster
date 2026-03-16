static hb_tag_t hb_ot_new_tag_from_script ( hb_script_t script ) {
 switch ( ( hb_tag_t ) script ) {
 case HB_SCRIPT_BENGALI : return HB_TAG ( 'b' , 'n' , 'g' , '2' ) ;
 case HB_SCRIPT_DEVANAGARI : return HB_TAG ( 'd' , 'e' , 'v' , '2' ) ;
 case HB_SCRIPT_GUJARATI : return HB_TAG ( 'g' , 'j' , 'r' , '2' ) ;
 case HB_SCRIPT_GURMUKHI : return HB_TAG ( 'g' , 'u' , 'r' , '2' ) ;
 case HB_SCRIPT_KANNADA : return HB_TAG ( 'k' , 'n' , 'd' , '2' ) ;
 case HB_SCRIPT_MALAYALAM : return HB_TAG ( 'm' , 'l' , 'm' , '2' ) ;
 case HB_SCRIPT_ORIYA : return HB_TAG ( 'o' , 'r' , 'y' , '2' ) ;
 case HB_SCRIPT_TAMIL : return HB_TAG ( 't' , 'm' , 'l' , '2' ) ;
 case HB_SCRIPT_TELUGU : return HB_TAG ( 't' , 'e' , 'l' , '2' ) ;
 case HB_SCRIPT_MYANMAR : return HB_TAG ( 'm' , 'y' , 'm' , '2' ) ;
 }
 return HB_OT_TAG_DEFAULT_SCRIPT ;
 }