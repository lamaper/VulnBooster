static int dissect_handle ( proto_tree * tree , packet_info * pinfo , gint hf , tvbuff_t * tvb , gint offset , bluetooth_data_t * bluetooth_data , bluetooth_uuid_t * uuid , gint32 handle ) {
 proto_item * handle_item ;
 proto_item * sub_item ;
 proto_tree * sub_tree ;
 bluetooth_uuid_t service_uuid ;
 bluetooth_uuid_t characteristic_uuid ;
 bluetooth_uuid_t attribute_uuid ;
 if ( handle == HANDLE_TVB ) {
 handle_item = proto_tree_add_item ( tree , hf , tvb , offset , 2 , ENC_LITTLE_ENDIAN ) ;
 handle = tvb_get_guint16 ( tvb , offset , ENC_LITTLE_ENDIAN ) ;
 }
 else if ( handle >= 0 && handle <= G_MAXUINT16 ) {
 handle_item = proto_tree_add_uint ( tree , hf , tvb , 0 , 0 , handle ) ;
 PROTO_ITEM_SET_GENERATED ( handle_item ) ;
 }
 else {
 DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 }
 service_uuid = get_service_uuid_from_handle ( pinfo , ( guint16 ) handle , bluetooth_data ) ;
 characteristic_uuid = get_characteristic_uuid_from_handle ( pinfo , ( guint16 ) handle , bluetooth_data ) ;
 attribute_uuid = get_uuid_from_handle ( pinfo , ( guint16 ) handle , bluetooth_data ) ;
 proto_item_append_text ( handle_item , " (" ) ;
 if ( memcmp ( & service_uuid , & attribute_uuid , sizeof ( attribute_uuid ) ) ) {
 if ( service_uuid . size == 2 || service_uuid . size == 16 ) {
 proto_item_append_text ( handle_item , "%s: " , print_uuid ( & service_uuid ) ) ;
 sub_tree = proto_item_add_subtree ( handle_item , ett_btatt_handle ) ;
 if ( service_uuid . size == 2 ) sub_item = proto_tree_add_uint ( sub_tree , hf_btatt_service_uuid16 , tvb , 0 , 0 , service_uuid . bt_uuid ) ;
 else sub_item = proto_tree_add_bytes_with_length ( sub_tree , hf_btatt_service_uuid128 , tvb , 0 , 0 , service_uuid . data , 16 ) ;
 PROTO_ITEM_SET_GENERATED ( sub_item ) ;
 }
 }
 if ( memcmp ( & characteristic_uuid , & attribute_uuid , sizeof ( attribute_uuid ) ) ) {
 if ( characteristic_uuid . size == 2 || characteristic_uuid . size == 16 ) {
 proto_item_append_text ( handle_item , "%s: " , print_uuid ( & characteristic_uuid ) ) ;
 sub_tree = proto_item_add_subtree ( handle_item , ett_btatt_handle ) ;
 if ( characteristic_uuid . size == 2 ) sub_item = proto_tree_add_uint ( sub_tree , hf_btatt_characteristic_uuid16 , tvb , 0 , 0 , characteristic_uuid . bt_uuid ) ;
 else sub_item = proto_tree_add_bytes_with_length ( sub_tree , hf_btatt_characteristic_uuid128 , tvb , 0 , 0 , characteristic_uuid . data , 16 ) ;
 PROTO_ITEM_SET_GENERATED ( sub_item ) ;
 }
 }
 proto_item_append_text ( handle_item , "%s)" , print_uuid ( & attribute_uuid ) ) ;
 if ( attribute_uuid . size == 2 || attribute_uuid . size == 16 ) {
 sub_tree = proto_item_add_subtree ( handle_item , ett_btatt_handle ) ;
 if ( attribute_uuid . size == 2 ) sub_item = proto_tree_add_uint ( sub_tree , hf_btatt_uuid16 , tvb , 0 , 0 , attribute_uuid . bt_uuid ) ;
 else sub_item = proto_tree_add_bytes_with_length ( sub_tree , hf_btatt_uuid128 , tvb , 0 , 0 , attribute_uuid . data , 16 ) ;
 PROTO_ITEM_SET_GENERATED ( sub_item ) ;
 }
 if ( uuid ) * uuid = attribute_uuid ;
 return offset + 2 ;
 }