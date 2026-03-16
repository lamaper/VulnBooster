static int parse_CFullPropSpec ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , proto_tree * pad_tree , struct CFullPropSpec * v , const char * fmt , ... ) {
 struct GuidPropertySet * pset ;
 const char * id_str , * guid_str , * txt ;
 proto_item * item ;
 proto_tree * tree ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CFullPropSpec , & item , txt ) ;
 offset = parse_padding ( tvb , offset , 8 , pad_tree , "paddingPropSet" ) ;
 offset = parse_guid ( tvb , offset , tree , & v -> guid , "GUID" ) ;
 pset = GuidPropertySet_find_guid ( & v -> guid ) ;
 offset = parse_PRSPEC_Kind ( tvb , offset , tree , & v -> kind ) ;
 v -> u . propid = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_cfullpropspec_propid , tvb , offset , 4 , v -> u . propid ) ;
 offset += 4 ;
 if ( v -> kind == PRSPEC_LPWSTR ) {
 int len = 2 * v -> u . propid ;
 proto_tree_add_item_ret_string ( tree , hf_mswsp_cfullpropspec_propname , tvb , offset , len , ENC_LITTLE_ENDIAN | ENC_UCS_2 , wmem_packet_scope ( ) , & v -> u . name ) ;
 offset += len ;
 }
 id_str = pset ? try_val_to_str ( v -> u . propid , pset -> id_map ) : NULL ;
 if ( id_str ) {
 proto_item_append_text ( item , ": %s" , id_str ) ;
 }
 else {
 guid_str = guids_get_guid_name ( & v -> guid ) ;
 if ( guid_str ) {
 proto_item_append_text ( item , ": \"%s\"" , guid_str ) ;
 }
 else {
 guid_str = guid_to_str ( wmem_packet_scope ( ) , & v -> guid ) ;
 proto_item_append_text ( item , ": {
%s}
" , guid_str ) ;
 }
 if ( v -> kind == PRSPEC_LPWSTR ) {
 proto_item_append_text ( item , " \"%s\"" , v -> u . name ) ;
 }
 else if ( v -> kind == PRSPEC_PROPID ) {
 proto_item_append_text ( item , " 0x%08x" , v -> u . propid ) ;
 }
 else {
 proto_item_append_text ( item , " <INVALID>" ) ;
 }
 }
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }