static void dissect_rsvp_xro_subobjects ( proto_tree * ti , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class ) {
 int i , lbit , type , l ;
 proto_tree * rsvp_xro_subtree ;
 int tree_type ;
 switch ( rsvp_class ) {
 case RSVP_CLASS_EXCLUDE_ROUTE : tree_type = TREE ( TT_EXCLUDE_ROUTE_SUBOBJ ) ;
 break ;
 default : return ;
 }
 for ( i = 1 , l = 0 ;
 l < obj_length - 4 ;
 i ++ ) {
 lbit = tvb_get_guint8 ( tvb , offset + l ) & 0x80 ;
 type = tvb_get_guint8 ( tvb , offset + l ) & 0x7f ;
 switch ( type ) {
 case 1 : rsvp_xro_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + l , 8 , tree_type , NULL , "IPv4 Subobject - %s" , tvb_ip_to_str ( tvb , offset + l + 2 ) ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_lbit , tvb , offset + l , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_type , tvb , offset + l , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_len , tvb , offset + l + 1 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_ipv4_addr , tvb , offset + l + 2 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_ipv4_prefix , tvb , offset + l + 6 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_ipv4_attr , tvb , offset + l + 7 , 1 , ENC_BIG_ENDIAN ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "IPv4 %s%s" , tvb_ip_to_str ( tvb , offset + l + 2 ) , lbit ? " [L]" : "" ) ;
 }
 break ;
 case 2 : rsvp_xro_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + l , 20 , tree_type , NULL , "IPv6 Subobject - %s" , tvb_ip6_to_str ( tvb , offset + l + 2 ) ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_lbit , tvb , offset + l , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_type , tvb , offset + l , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_len , tvb , offset + l + 1 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_ipv6_addr , tvb , offset + l + 2 , 16 , ENC_NA ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_ipv6_prefix , tvb , offset + l + 18 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_ipv6_attr , tvb , offset + l + 19 , 1 , ENC_BIG_ENDIAN ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "IPv6 [...]%s" , lbit ? " [L]" : "" ) ;
 }
 break ;
 case 34 : rsvp_xro_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + l , 8 , tree_type , NULL , "SRLG Subobject - %u" , tvb_get_ntohl ( tvb , offset + l + 2 ) ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_lbit , tvb , offset + l , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_type , tvb , offset + l , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_len , tvb , offset + l + 1 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_srlg_id , tvb , offset + l + 2 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_srlg_res , tvb , offset + l + 6 , 2 , ENC_BIG_ENDIAN ) ;
 if ( i < 4 ) {
 proto_item_append_text ( ti , "SRLG %u%s" , tvb_get_ntohl ( tvb , offset + l + 2 ) , lbit ? " [L]" : "" ) ;
 }
 break ;
 default : rsvp_xro_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + l , tvb_get_guint8 ( tvb , offset + l + 1 ) , tree_type , NULL , "Unknown subobject: %d" , type ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_lbit , tvb , offset + l , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_type , tvb , offset + l , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_xro_subtree , hf_rsvp_xro_sobj_len , tvb , offset + l + 1 , 1 , ENC_BIG_ENDIAN ) ;
 break ;
 }
 if ( tvb_get_guint8 ( tvb , offset + l + 1 ) < 1 ) {
 proto_tree_add_expert_format ( rsvp_xro_subtree , pinfo , & ei_rsvp_invalid_length , tvb , offset + l + 1 , 1 , "Invalid Length: %u" , tvb_get_guint8 ( tvb , offset + l + 1 ) ) ;
 return ;
 }
 l += tvb_get_guint8 ( tvb , offset + l + 1 ) ;
 if ( l < obj_length - 4 ) {
 if ( i < 4 ) proto_item_append_text ( ti , ", " ) ;
 else if ( i == 4 ) proto_item_append_text ( ti , "..." ) ;
 }
 }
 }