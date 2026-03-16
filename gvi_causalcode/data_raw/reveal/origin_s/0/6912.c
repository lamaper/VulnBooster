static void dissect_rsvp_error ( proto_item * ti , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 int offset3 = 0 ;
 guint8 error_flags ;
 guint8 error_code ;
 guint16 error_val ;
 proto_tree * ti2 = NULL , * rsvp_error_subtree ;
 switch ( type ) {
 case 1 : {
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "1 - IPv4" ) ;
 if ( obj_length > 4 ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_error_error_node_ipv4 , tvb , offset2 , 4 , ENC_BIG_ENDIAN ) ;
 offset3 = offset2 + 4 ;
 }
 break ;
 }
 case 2 : {
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "2 - IPv6" ) ;
 if ( obj_length > 4 ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_error_error_node_ipv6 , tvb , offset2 , 16 , ENC_NA ) ;
 offset3 = offset2 + 16 ;
 }
 break ;
 }
 case 3 : {
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "3 - IPv4 IF-ID" ) ;
 if ( obj_length > 4 ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_error_error_node_ipv4 , tvb , offset2 , 4 , ENC_BIG_ENDIAN ) ;
 offset3 = offset2 + 4 ;
 }
 break ;
 }
 case 4 : {
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "4 - IPv6 IF-ID" ) ;
 if ( obj_length > 16 ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_error_error_node_ipv6 , tvb , offset2 , 16 , ENC_NA ) ;
 offset3 = offset2 + 16 ;
 }
 break ;
 }
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 if ( obj_length > 4 ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_error_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 }
 return ;
 }
 if ( obj_length > 4 ) {
 error_flags = tvb_get_guint8 ( tvb , offset3 ) ;
 ti2 = proto_tree_add_item ( rsvp_object_tree , hf_rsvp_error_flags , tvb , offset3 , 1 , ENC_BIG_ENDIAN ) ;
 rsvp_error_subtree = proto_item_add_subtree ( ti2 , TREE ( TT_ERROR_FLAGS ) ) ;
 proto_tree_add_item ( rsvp_error_subtree , hf_rsvp_error_flags_path_state_removed , tvb , offset3 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_error_subtree , hf_rsvp_error_flags_not_guilty , tvb , offset3 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_error_subtree , hf_rsvp_error_flags_in_place , tvb , offset3 , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti2 , " %s %s %s" , ( error_flags & ( 1U << 2 ) ) ? "Path-State-Removed" : "" , ( error_flags & ( 1U << 1 ) ) ? "NotGuilty" : "" , ( error_flags & ( 1U << 0 ) ) ? "InPlace" : "" ) ;
 error_code = tvb_get_guint8 ( tvb , offset3 + 1 ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_error_error_code , tvb , offset3 + 1 , 1 , ENC_BIG_ENDIAN ) ;
 error_val = dissect_rsvp_error_value ( rsvp_object_tree , tvb , offset3 + 2 , error_code ) ;
 switch ( type ) {
 case 1 : proto_item_set_text ( ti , "ERROR: IPv4, Error code: %s, Value: %d, Error Node: %s" , val_to_str_ext ( error_code , & rsvp_error_codes_ext , "Unknown (%d)" ) , error_val , tvb_ip_to_str ( tvb , offset2 ) ) ;
 break ;
 case 3 : proto_item_set_text ( ti , "ERROR: IPv4 IF-ID, Error code: %s, Value: %d, Control Node: %s. " , val_to_str_ext ( error_code , & rsvp_error_codes_ext , "Unknown (%d)" ) , error_val , tvb_ip_to_str ( tvb , offset2 ) ) ;
 dissect_rsvp_ifid_tlv ( ti , pinfo , rsvp_object_tree , tvb , offset + 12 , obj_length - 12 , TREE ( TT_ERROR_SUBOBJ ) ) ;
 break ;
 }
 }
 }