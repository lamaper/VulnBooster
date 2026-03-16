void netbios_add_name ( const char * label , tvbuff_t * tvb , int offset , proto_tree * tree ) {
 proto_tree * field_tree ;
 char name_str [ ( NETBIOS_NAME_LEN - 1 ) * 4 + 1 ] ;
 int name_type ;
 const char * name_type_str ;
 name_type = get_netbios_name ( tvb , offset , name_str , ( NETBIOS_NAME_LEN - 1 ) * 4 + 1 ) ;
 name_type_str = netbios_name_type_descr ( name_type ) ;
 field_tree = proto_tree_add_subtree_format ( tree , tvb , offset , NETBIOS_NAME_LEN , ett_netb_name , NULL , "%s: %s<%02x> (%s)" , label , name_str , name_type , name_type_str ) ;
 proto_tree_add_string_format ( field_tree , hf_netb_nb_name , tvb , offset , 15 , name_str , "%s" , name_str ) ;
 proto_tree_add_uint_format ( field_tree , hf_netb_nb_name_type , tvb , offset + 15 , 1 , name_type , "0x%02x (%s)" , name_type , name_type_str ) ;
 }