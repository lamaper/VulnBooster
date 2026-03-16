static void lbmpdm_definition_build_key ( guint32 * key_value , wmem_tree_key_t * key , guint64 channel , guint32 id , guint8 version_major , guint8 version_minor ) {
 key_value [ LBMPDM_DEFINITION_KEY_ELEMENT_CHANNEL_HIGH ] = ( guint32 ) ( ( channel >> 32 ) & 0xffffffff ) ;
 key_value [ LBMPDM_DEFINITION_KEY_ELEMENT_CHANNEL_LOW ] = ( guint32 ) ( channel & 0xffffffff ) ;
 key_value [ LBMPDM_DEFINITION_KEY_ELEMENT_ID ] = id ;
 key_value [ LBMPDM_DEFINITION_KEY_ELEMENT_VERS_MAJOR ] = version_major ;
 key_value [ LBMPDM_DEFINITION_KEY_ELEMENT_VERS_MINOR ] = version_minor ;
 key [ 0 ] . length = LBMPDM_DEFINITION_KEY_ELEMENT_COUNT ;
 key [ 0 ] . key = key_value ;
 key [ 1 ] . length = 0 ;
 key [ 1 ] . key = NULL ;
 }