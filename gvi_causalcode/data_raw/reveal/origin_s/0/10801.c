static int dissect_diameter_base_framed_ipv6_prefix ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , void * data ) {
 diam_sub_dis_t * diam_sub_dis = ( diam_sub_dis_t * ) data ;
 guint8 prefix_len , prefix_len_bytes ;
 proto_item * pi ;
 proto_tree_add_item ( tree , hf_framed_ipv6_prefix_reserved , tvb , 0 , 1 , ENC_BIG_ENDIAN ) ;
 pi = proto_tree_add_item ( tree , hf_framed_ipv6_prefix_length , tvb , 1 , 1 , ENC_BIG_ENDIAN ) ;
 prefix_len = tvb_get_guint8 ( tvb , 1 ) ;
 if ( prefix_len > 128 ) {
 expert_add_info ( pinfo , pi , & ei_diameter_invalid_ipv6_prefix_len ) ;
 }
 prefix_len_bytes = prefix_len / 8 ;
 if ( prefix_len % 8 ) prefix_len_bytes ++ ;
 proto_tree_add_item ( tree , hf_framed_ipv6_prefix_bytes , tvb , 2 , prefix_len_bytes , ENC_NA ) ;
 if ( prefix_len_bytes == 16 ) {
 proto_tree_add_item ( tree , hf_framed_ipv6_prefix_ipv6 , tvb , 2 , prefix_len_bytes , ENC_NA ) ;
 }
 else if ( prefix_len_bytes < 16 ) {
 struct e_in6_addr value ;
 address addr ;
 memset ( & value . bytes , 0 , sizeof ( value ) ) ;
 tvb_memcpy ( tvb , ( guint8 * ) & value . bytes , 2 , prefix_len_bytes ) ;
 value . bytes [ prefix_len_bytes ] = value . bytes [ prefix_len_bytes ] & ( 0xff << ( prefix_len % 8 ) ) ;
 proto_tree_add_ipv6 ( tree , hf_framed_ipv6_prefix_ipv6 , tvb , 2 , prefix_len_bytes , & value ) ;
 set_address ( & addr , AT_IPv6 , 16 , value . bytes ) ;
 diam_sub_dis -> avp_str = wmem_strdup_printf ( wmem_packet_scope ( ) , "%s/%u" , address_to_str ( wmem_packet_scope ( ) , & addr ) , prefix_len ) ;
 }
 return ( prefix_len_bytes + 2 ) ;
 }