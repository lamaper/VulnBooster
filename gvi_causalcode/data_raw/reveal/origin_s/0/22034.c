static const char * utf8_avp ( diam_ctx_t * c , diam_avp_t * a , tvbuff_t * tvb , diam_sub_dis_t * diam_sub_dis_inf _U_ ) {
 char * label = NULL ;
 if ( c -> tree ) {
 proto_item * pi = proto_tree_add_item ( c -> tree , a -> hf_value , tvb , 0 , tvb_reported_length ( tvb ) , ENC_UTF_8 | ENC_BIG_ENDIAN ) ;
 label = ( char * ) wmem_alloc ( wmem_packet_scope ( ) , ITEM_LABEL_LENGTH + 1 ) ;
 proto_item_fill_label ( PITEM_FINFO ( pi ) , label ) ;
 label = strstr ( label , ": " ) + 2 ;
 }
 return label ;
 }