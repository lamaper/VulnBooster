static const char * address_rfc_avp ( diam_ctx_t * c , diam_avp_t * a , tvbuff_t * tvb , diam_sub_dis_t * diam_sub_dis_inf _U_ ) {
 char * label = NULL ;
 address_avp_t * t = ( address_avp_t * ) a -> type_data ;
 gint len = tvb_reported_length ( tvb ) ;
 proto_item * pi = proto_tree_add_item ( c -> tree , a -> hf_value , tvb , 0 , len , ENC_BIG_ENDIAN ) ;
 proto_tree * pt = proto_item_add_subtree ( pi , t -> ett ) ;
 guint32 addr_type = tvb_get_ntohs ( tvb , 0 ) ;
 len = len - 2 ;
 proto_tree_add_item ( pt , t -> hf_address_type , tvb , 0 , 2 , ENC_NA ) ;
 switch ( addr_type ) {
 case 1 : if ( len != 4 ) {
 proto_tree_add_expert_format ( pt , c -> pinfo , & ei_diameter_avp_len , tvb , 2 , len , "Wrong length for IPv4 Address: %d instead of 4" , len ) ;
 return "[Malformed]" ;
 }
 pi = proto_tree_add_item ( pt , t -> hf_ipv4 , tvb , 2 , 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case 2 : if ( len != 16 ) {
 proto_tree_add_expert_format ( pt , c -> pinfo , & ei_diameter_avp_len , tvb , 2 , len , "Wrong length for IPv6 Address: %d instead of 16" , len ) ;
 return "[Malformed]" ;
 }
 pi = proto_tree_add_item ( pt , t -> hf_ipv6 , tvb , 2 , 16 , ENC_NA ) ;
 break ;
 default : pi = proto_tree_add_item ( pt , t -> hf_other , tvb , 2 , - 1 , ENC_BIG_ENDIAN ) ;
 break ;
 }
 if ( c -> tree ) {
 label = ( char * ) wmem_alloc ( wmem_packet_scope ( ) , ITEM_LABEL_LENGTH + 1 ) ;
 proto_item_fill_label ( PITEM_FINFO ( pi ) , label ) ;
 label = strstr ( label , ": " ) + 2 ;
 }
 return label ;
 }