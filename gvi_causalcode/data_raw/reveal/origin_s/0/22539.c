static hb_tag_t hb_ot_old_tag_from_script ( hb_script_t script ) {
 switch ( ( hb_tag_t ) script ) {
 case HB_SCRIPT_INVALID : return HB_OT_TAG_DEFAULT_SCRIPT ;
 case HB_SCRIPT_HIRAGANA : return HB_TAG ( 'k' , 'a' , 'n' , 'a' ) ;
 case HB_SCRIPT_LAO : return HB_TAG ( 'l' , 'a' , 'o' , ' ' ) ;
 case HB_SCRIPT_YI : return HB_TAG ( 'y' , 'i' , ' ' , ' ' ) ;
 case HB_SCRIPT_NKO : return HB_TAG ( 'n' , 'k' , 'o' , ' ' ) ;
 case HB_SCRIPT_VAI : return HB_TAG ( 'v' , 'a' , 'i' , ' ' ) ;
 }
 return ( ( hb_tag_t ) script ) | 0x20000000u ;
 }