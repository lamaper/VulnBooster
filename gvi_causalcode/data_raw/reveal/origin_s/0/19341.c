static int parse_CDbColId ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , proto_tree * pad_tree , const char * text ) {
 guint32 eKind , ulId ;
 e_guid_t guid ;
 const char * str ;
 static const char * KIND [ ] = {
 "DBKIND_GUID_NAME" , "DBKIND_GUID_PROPID" }
 ;
 proto_item * tree_item ;
 proto_tree * tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CDbColId , & tree_item , text ) ;
 eKind = tvb_get_letohl ( tvb , offset ) ;
 str = ( eKind < 2 ? KIND [ eKind ] : "???" ) ;
 proto_tree_add_string_format_value ( tree , hf_mswsp_cdbcolid_ekind , tvb , offset , 4 , str , "%s (%u)" , str , eKind ) ;
 offset += 4 ;
 offset = parse_padding ( tvb , offset , 8 , pad_tree , "paddingGuidAlign" ) ;
 offset = parse_guid ( tvb , offset , tree , & guid , "GUID" ) ;
 ulId = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_cdbcolid_ulid , tvb , offset , 4 , ulId ) ;
 offset += 4 ;
 if ( eKind == DBKIND_GUID_NAME ) {
 char * name ;
 int len = ulId ;
 name = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset , len , ENC_LITTLE_ENDIAN | ENC_UCS_2 ) ;
 proto_item_append_text ( tree_item , " \"%s\"" , name ) ;
 proto_tree_add_string_format_value ( tree , hf_mswsp_cdbcolid_vstring , tvb , offset , len , name , "\"%s\"" , name ) ;
 offset += len ;
 }
 else if ( eKind == DBKIND_GUID_PROPID ) {
 proto_item_append_text ( tree_item , " %08x" , ulId ) ;
 }
 else {
 proto_item_append_text ( tree_item , "<INVALID>" ) ;
 }
 proto_item_set_end ( tree_item , tvb , offset ) ;
 return offset ;
 }