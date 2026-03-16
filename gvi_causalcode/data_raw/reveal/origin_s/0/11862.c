static int parse_guid ( tvbuff_t * tvb , int offset , proto_tree * tree , e_guid_t * guid , const char * text ) {
 const char * guid_str , * name , * bytes ;
 proto_tree * tr ;
 tvb_get_letohguid ( tvb , offset , guid ) ;
 guid_str = guid_to_str ( wmem_packet_scope ( ) , guid ) ;
 name = guids_get_guid_name ( guid ) ;
 tr = proto_tree_add_subtree_format ( tree , tvb , offset , 16 , ett_GUID , NULL , "%s: %s {
%s}
" , text , name ? name : "" , guid_str ) ;
 proto_tree_add_item ( tr , hf_mswsp_guid_time_low , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tr , hf_mswsp_guid_time_mid , tvb , offset , 2 , ENC_LITTLE_ENDIAN ) ;
 offset += 2 ;
 proto_tree_add_item ( tr , hf_mswsp_guid_time_high , tvb , offset , 2 , ENC_LITTLE_ENDIAN ) ;
 offset += 2 ;
 proto_tree_add_item ( tr , hf_mswsp_guid_time_clock_hi , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 offset += 1 ;
 proto_tree_add_item ( tr , hf_mswsp_guid_time_clock_low , tvb , offset , 1 , ENC_LITTLE_ENDIAN ) ;
 offset += 1 ;
 bytes = bytestring_to_str ( wmem_packet_scope ( ) , & guid -> data4 [ 2 ] , 6 , ':' ) ;
 proto_tree_add_string ( tr , hf_mswsp_guid_node , tvb , offset , 6 , bytes ) ;
 offset += 6 ;
 return offset ;
 }