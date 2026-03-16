static lbmpdm_definition_field_t * lbmpdm_definition_field_add ( lbmpdm_definition_t * definition , guint32 id ) {
 lbmpdm_definition_field_t * entry = NULL ;
 entry = lbmpdm_definition_field_find ( definition , id ) ;
 if ( entry != NULL ) {
 return ( entry ) ;
 }
 entry = wmem_new0 ( wmem_file_scope ( ) , lbmpdm_definition_field_t ) ;
 entry -> id = id ;
 entry -> definition = definition ;
 wmem_tree_insert32 ( definition -> field_list , id , ( void * ) entry ) ;
 return ( entry ) ;
 }