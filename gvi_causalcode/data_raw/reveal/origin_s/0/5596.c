static const char * integer32_avp ( diam_ctx_t * c , diam_avp_t * a , tvbuff_t * tvb , diam_sub_dis_t * diam_sub_dis_inf _U_ ) {
 char * label = NULL ;
 proto_item * pi ;
 gint length = tvb_reported_length ( tvb ) ;
 if ( length == 4 ) {
 if ( c -> tree ) {
 pi = proto_tree_add_item ( c -> tree , a -> hf_value , tvb , 0 , length , ENC_BIG_ENDIAN ) ;
 label = ( char * ) wmem_alloc ( wmem_packet_scope ( ) , ITEM_LABEL_LENGTH + 1 ) ;
 proto_item_fill_label ( PITEM_FINFO ( pi ) , label ) ;
 label = strstr ( label , ": " ) + 2 ;
 }
 }
 else {
 pi = proto_tree_add_bytes_format ( c -> tree , hf_diameter_avp_data_wrong_length , tvb , 0 , length , NULL , "Error! Bad Integer32 Length" ) ;
 expert_add_info_format ( c -> pinfo , pi , & ei_diameter_avp_len , "Bad Integer32 Length (%u)" , length ) ;
 PROTO_ITEM_SET_GENERATED ( pi ) ;
 }
 return label ;
 }