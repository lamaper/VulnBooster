static gint btatt_dissect_attribute_handle ( guint16 handle , tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , btatt_data_t * att_data ) {
 proto_item * main_item ;
 proto_tree * main_tree ;
 proto_item * patron_item = NULL ;
 bluetooth_uuid_t uuid ;
 dissector_handle_t attribute_handler ;
 const char * attribute_name ;
 attribute_handler = dissector_get_uint_handle ( att_handle_dissector_table , handle ) ;
 if ( attribute_handler == NULL ) return 0 ;
 main_item = proto_tree_add_item ( tree , dissector_handle_get_protocol_index ( attribute_handler ) , tvb , 0 , tvb_captured_length ( tvb ) , ENC_NA ) ;
 main_tree = proto_item_add_subtree ( main_item , ett_btgatt ) ;
 attribute_name = dissector_handle_get_short_name ( attribute_handler ) ;
 if ( strlen ( attribute_name ) > 7 ) {
 uuid . size = 2 ;
 uuid . bt_uuid = ( guint16 ) g_ascii_strtoull ( attribute_name + strlen ( attribute_name ) - 7 , NULL , 16 ) ;
 uuid . data [ 1 ] = uuid . bt_uuid & 0xFF ;
 uuid . data [ 0 ] = ( uuid . bt_uuid >> 8 ) & 0xFF ;
 }
 else {
 uuid . size = 2 ;
 uuid . bt_uuid = 0 ;
 }
 return dissect_attribute_value ( main_tree , patron_item , pinfo , tvb , 0 , tvb_captured_length ( tvb ) , 0 , uuid , att_data ) ;
 }