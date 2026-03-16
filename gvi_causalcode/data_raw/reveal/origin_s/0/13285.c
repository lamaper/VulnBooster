static int dissect_btgatt ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 proto_item * main_item ;
 proto_tree * main_tree ;
 proto_item * patron_item = NULL ;
 bluetooth_uuid_t uuid ;
 main_item = proto_tree_add_item ( tree , ( gint ) GPOINTER_TO_UINT ( wmem_list_frame_data ( wmem_list_tail ( pinfo -> layers ) ) ) , tvb , 0 , tvb_captured_length ( tvb ) , ENC_NA ) ;
 main_tree = proto_item_add_subtree ( main_item , ett_btgatt ) ;
 if ( strlen ( pinfo -> current_proto ) > 7 ) {
 uuid . size = 2 ;
 uuid . bt_uuid = ( guint16 ) g_ascii_strtoull ( pinfo -> current_proto + strlen ( pinfo -> current_proto ) - 7 , NULL , 16 ) ;
 uuid . data [ 1 ] = uuid . bt_uuid & 0xFF ;
 uuid . data [ 0 ] = ( uuid . bt_uuid >> 8 ) & 0xFF ;
 }
 else {
 uuid . size = 2 ;
 uuid . bt_uuid = 0 ;
 }
 return dissect_attribute_value ( main_tree , patron_item , pinfo , tvb , 0 , tvb_captured_length ( tvb ) , 0 , uuid , ( btatt_data_t * ) data ) ;
 }