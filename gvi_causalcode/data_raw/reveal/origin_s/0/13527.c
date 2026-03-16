static hb_script_t hb_ot_old_tag_to_script ( hb_tag_t tag ) {
 if ( unlikely ( tag == HB_OT_TAG_DEFAULT_SCRIPT ) ) return HB_SCRIPT_INVALID ;
 if ( unlikely ( ( tag & 0x0000FF00u ) == 0x00002000u ) ) tag |= ( tag >> 8 ) & 0x0000FF00u ;
 if ( unlikely ( ( tag & 0x000000FFu ) == 0x00000020u ) ) tag |= ( tag >> 8 ) & 0x000000FFu ;
 return ( hb_script_t ) ( tag & ~ 0x20000000u ) ;
 }