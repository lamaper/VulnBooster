static const char * time_avp ( diam_ctx_t * c , diam_avp_t * a , tvbuff_t * tvb , diam_sub_dis_t * diam_sub_dis_inf _U_ ) {
 int len = tvb_reported_length ( tvb ) ;
 char * label = NULL ;
 proto_item * pi ;
 if ( len != 4 ) {
 proto_tree_add_expert_format ( c -> tree , c -> pinfo , & ei_diameter_avp_len , tvb , 0 , 4 , "Bad Timestamp Length: %d instead of 4" , len ) ;
 return "[Malformed]" ;
 }
 if ( c -> tree ) {
 label = ( char * ) wmem_alloc ( wmem_packet_scope ( ) , ITEM_LABEL_LENGTH + 1 ) ;
 pi = proto_tree_add_item ( c -> tree , ( a -> hf_value ) , tvb , 0 , 4 , ENC_TIME_NTP | ENC_BIG_ENDIAN ) ;
 proto_item_fill_label ( PITEM_FINFO ( pi ) , label ) ;
 label = strstr ( label , ": " ) + 2 ;
 }
 return label ;
 }