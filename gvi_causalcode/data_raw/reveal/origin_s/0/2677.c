void hb_ot_tags_from_script ( hb_script_t script , hb_tag_t * script_tag_1 , hb_tag_t * script_tag_2 ) {
 hb_tag_t new_tag ;
 * script_tag_2 = HB_OT_TAG_DEFAULT_SCRIPT ;
 * script_tag_1 = hb_ot_old_tag_from_script ( script ) ;
 new_tag = hb_ot_new_tag_from_script ( script ) ;
 if ( unlikely ( new_tag != HB_OT_TAG_DEFAULT_SCRIPT ) ) {
 * script_tag_2 = * script_tag_1 ;
 * script_tag_1 = new_tag ;
 }
 }