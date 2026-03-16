static hb_script_t hb_ot_new_tag_to_script ( hb_tag_t tag ) {
 switch ( tag ) {
 case HB_TAG ( 'b' , 'n' , 'g' , '2' ) : return HB_SCRIPT_BENGALI ;
 case HB_TAG ( 'd' , 'e' , 'v' , '2' ) : return HB_SCRIPT_DEVANAGARI ;
 case HB_TAG ( 'g' , 'j' , 'r' , '2' ) : return HB_SCRIPT_GUJARATI ;
 case HB_TAG ( 'g' , 'u' , 'r' , '2' ) : return HB_SCRIPT_GURMUKHI ;
 case HB_TAG ( 'k' , 'n' , 'd' , '2' ) : return HB_SCRIPT_KANNADA ;
 case HB_TAG ( 'm' , 'l' , 'm' , '2' ) : return HB_SCRIPT_MALAYALAM ;
 case HB_TAG ( 'o' , 'r' , 'y' , '2' ) : return HB_SCRIPT_ORIYA ;
 case HB_TAG ( 't' , 'm' , 'l' , '2' ) : return HB_SCRIPT_TAMIL ;
 case HB_TAG ( 't' , 'e' , 'l' , '2' ) : return HB_SCRIPT_TELUGU ;
 case HB_TAG ( 'm' , 'y' , 'm' , '2' ) : return HB_SCRIPT_MYANMAR ;
 }
 return HB_SCRIPT_UNKNOWN ;
 }