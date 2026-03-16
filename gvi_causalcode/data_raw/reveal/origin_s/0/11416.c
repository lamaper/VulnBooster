static void add_opt_rr_to_tree ( proto_tree * rr_tree , tvbuff_t * tvb , int offset , const char * name , int namelen , gboolean is_mdns ) {
 proto_tree * Z_tree ;
 proto_item * Z_item ;
 proto_tree_add_string ( rr_tree , hf_dns_rr_name , tvb , offset , namelen , name ) ;
 offset += namelen ;
 proto_tree_add_item ( rr_tree , hf_dns_rr_type , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 2 ;
 if ( is_mdns ) {
 proto_tree_add_item ( rr_tree , hf_dns_rr_udp_payload_size_mdns , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rr_tree , hf_dns_rr_cache_flush , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 }
 else {
 proto_tree_add_item ( rr_tree , hf_dns_rr_udp_payload_size , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 }
 offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_rr_ext_rcode , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 proto_tree_add_item ( rr_tree , hf_dns_rr_edns0_version , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 Z_item = proto_tree_add_item ( rr_tree , hf_dns_rr_z , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 Z_tree = proto_item_add_subtree ( Z_item , ett_dns_rr ) ;
 proto_tree_add_item ( Z_tree , hf_dns_rr_z_do , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( Z_tree , hf_dns_rr_z_reserved , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset += 2 ;
 proto_tree_add_item ( rr_tree , hf_dns_rr_len , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 }