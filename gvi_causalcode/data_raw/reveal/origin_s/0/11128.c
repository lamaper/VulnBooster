void parseQualifiedName ( proto_tree * tree , tvbuff_t * tvb , packet_info * pinfo , gint * pOffset , const char * szFieldName ) {
 proto_item * ti ;
 proto_tree * subtree = proto_tree_add_subtree_format ( tree , tvb , * pOffset , - 1 , ett_opcua_qualifiedname , & ti , "%s: QualifiedName" , szFieldName ) ;
 parseUInt16 ( subtree , tvb , pinfo , pOffset , hf_opcua_qualifiedname_id ) ;
 parseString ( subtree , tvb , pinfo , pOffset , hf_opcua_qualifiedname_name ) ;
 proto_item_set_end ( ti , tvb , * pOffset ) ;
 }