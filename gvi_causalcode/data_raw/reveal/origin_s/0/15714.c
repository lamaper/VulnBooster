static lbmpdm_definition_t * lbmpdm_definition_add ( guint64 channel , guint32 id , guint8 version_major , guint8 version_minor ) {
 lbmpdm_definition_t * entry = NULL ;
 guint32 keyval [ LBMPDM_DEFINITION_KEY_ELEMENT_COUNT ] ;
 wmem_tree_key_t tkey [ 2 ] ;
 entry = lbmpdm_definition_find ( channel , id , version_major , version_minor ) ;
 if ( entry != NULL ) {
 return ( entry ) ;
 }
 entry = wmem_new ( wmem_file_scope ( ) , lbmpdm_definition_t ) ;
 entry -> channel = channel ;
 entry -> id = id ;
 entry -> vers_major = version_major ;
 entry -> vers_minor = version_minor ;
 entry -> field_list = wmem_tree_new ( wmem_file_scope ( ) ) ;
 lbmpdm_definition_build_key ( keyval , tkey , channel , id , version_major , version_minor ) ;
 wmem_tree_insert32_array ( lbmpdm_definition_table , tkey , ( void * ) entry ) ;
 return ( entry ) ;
 }