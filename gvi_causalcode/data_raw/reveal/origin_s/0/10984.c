static gint dissect_gatt_uuid ( proto_tree * tree , packet_info * pinfo , tvbuff_t * tvb , gint offset ) {
 proto_item * sub_item ;
 bluetooth_uuid_t sub_uuid ;
 if ( tvb_reported_length_remaining ( tvb , offset ) == 2 ) {
 proto_tree_add_item ( tree , hf_btatt_uuid16 , tvb , offset , 2 , ENC_LITTLE_ENDIAN ) ;
 sub_uuid = get_uuid ( tvb , offset , 2 ) ;
 offset += 2 ;
 }
 else if ( tvb_reported_length_remaining ( tvb , offset ) == 16 ) {
 sub_item = proto_tree_add_item ( tree , hf_btatt_uuid128 , tvb , offset , 16 , ENC_NA ) ;
 sub_uuid = get_uuid ( tvb , offset , 16 ) ;
 proto_item_append_text ( sub_item , " (%s)" , print_uuid ( & sub_uuid ) ) ;
 offset += 16 ;
 }
 else {
 sub_item = proto_tree_add_item ( tree , hf_btatt_value , tvb , offset , - 1 , ENC_NA ) ;
 expert_add_info ( pinfo , sub_item , & ei_btatt_bad_data ) ;
 offset = tvb_captured_length ( tvb ) ;
 }
 return offset ;
 }