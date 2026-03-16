static void dissect_rsvp_scope ( proto_item * ti _U_ , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 int mylen ;
 mylen = obj_length - 4 ;
 switch ( type ) {
 case 1 : {
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "1 - IPv4" ) ;
 while ( mylen > 0 ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_scope_ipv4_address , tvb , offset2 , 4 , ENC_BIG_ENDIAN ) ;
 offset2 += 4 ;
 mylen -= 4 ;
 }
 break ;
 }
 case 2 : {
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "2 - IPv6" ) ;
 while ( mylen > 0 ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_scope_ipv6_address , tvb , offset2 , 16 , ENC_NA ) ;
 offset2 += 16 ;
 mylen -= 16 ;
 }
 break ;
 }
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_scope_data , tvb , offset2 , mylen , ENC_NA ) ;
 break ;
 }
 }