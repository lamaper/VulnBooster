hb_script_t hb_ot_tag_to_script ( hb_tag_t tag ) {
 if ( unlikely ( ( tag & 0x000000FFu ) == '2' ) ) return hb_ot_new_tag_to_script ( tag ) ;
 return hb_ot_old_tag_to_script ( tag ) ;
 }