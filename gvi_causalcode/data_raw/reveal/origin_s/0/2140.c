static lbmpdm_definition_field_t * lbmpdm_definition_field_find ( lbmpdm_definition_t * definition , guint32 id ) {
 lbmpdm_definition_field_t * entry = NULL ;
 entry = ( lbmpdm_definition_field_t * ) wmem_tree_lookup32 ( definition -> field_list , id ) ;
 return ( entry ) ;
 }