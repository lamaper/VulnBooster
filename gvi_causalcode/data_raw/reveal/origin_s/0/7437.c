static lbmpdm_definition_t * lbmpdm_definition_find ( guint64 channel , guint32 ID , guint8 version_major , guint8 version_minor ) {
 lbmpdm_definition_t * entry = NULL ;
 guint32 keyval [ LBMPDM_DEFINITION_KEY_ELEMENT_COUNT ] ;
 wmem_tree_key_t tkey [ 2 ] ;
 lbmpdm_definition_build_key ( keyval , tkey , channel , ID , version_major , version_minor ) ;
 entry = ( lbmpdm_definition_t * ) wmem_tree_lookup32_array ( lbmpdm_definition_table , tkey ) ;
 return ( entry ) ;
 }