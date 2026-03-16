static mac_is_sdu * get_sdu ( guint frame_num , guint16 tsn , guint8 type , mac_is_channel * ch ) {
 mac_is_sdu * sdu = NULL ;
 GHashTable * sdus = NULL ;
 mac_is_fragment frag_lookup_key ;
 sdus = ( GHashTable * ) g_hash_table_lookup ( mac_is_sdus , ch ) ;
 if ( sdus ) {
 frag_lookup_key . frame_num = frame_num ;
 frag_lookup_key . tsn = tsn ;
 frag_lookup_key . type = type ;
 sdu = ( mac_is_sdu * ) g_hash_table_lookup ( sdus , & frag_lookup_key ) ;
 return sdu ;
 }
 return NULL ;
 }