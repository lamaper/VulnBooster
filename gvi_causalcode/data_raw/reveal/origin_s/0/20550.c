static const char * address_v16_avp ( diam_ctx_t * c , diam_avp_t * a , tvbuff_t * tvb , diam_sub_dis_t * diam_sub_dis_inf _U_ ) {
 char * label = NULL ;
 address_avp_t * t = ( address_avp_t * ) a -> type_data ;
 proto_item * pi = proto_tree_add_item ( c -> tree , a -> hf_value , tvb , 0 , tvb_reported_length ( tvb ) , ENC_BIG_ENDIAN ) ;
 proto_tree * pt = proto_item_add_subtree ( pi , t -> ett ) ;
 guint32 len = tvb_reported_length ( tvb ) ;
 switch ( len ) {
 case 4 : pi = proto_tree_add_item ( pt , t -> hf_ipv4 , tvb , 0 , 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case 16 : pi = proto_tree_add_item ( pt , t -> hf_ipv6 , tvb , 0 , 16 , ENC_NA ) ;
 break ;
 default : pi = proto_tree_add_item ( pt , t -> hf_other , tvb , 0 , len , ENC_BIG_ENDIAN ) ;
 expert_add_info_format ( c -> pinfo , pi , & ei_diameter_avp_len , "Bad Address Length (%u)" , len ) ;
 break ;
 }
 if ( c -> tree ) {
 label = ( char * ) wmem_alloc ( wmem_packet_scope ( ) , ITEM_LABEL_LENGTH + 1 ) ;
 proto_item_fill_label ( PITEM_FINFO ( pi ) , label ) ;
 label = strstr ( label , ": " ) + 2 ;
 }
 return label ;
 }