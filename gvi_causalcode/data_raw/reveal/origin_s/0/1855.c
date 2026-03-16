static int dissect_diameter_3gpp2_exp_res ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , void * data ) {
 proto_item * pi ;
 diam_sub_dis_t * diam_sub_dis ;
 if ( data == NULL ) return 0 ;
 diam_sub_dis = ( diam_sub_dis_t * ) data ;
 if ( tree ) {
 pi = proto_tree_add_item ( tree , hf_diameter_3gpp2_exp_res , tvb , 0 , 4 , ENC_BIG_ENDIAN ) ;
 diam_sub_dis -> avp_str = ( char * ) wmem_alloc ( wmem_packet_scope ( ) , ITEM_LABEL_LENGTH + 1 ) ;
 proto_item_fill_label ( PITEM_FINFO ( pi ) , diam_sub_dis -> avp_str ) ;
 diam_sub_dis -> avp_str = strstr ( diam_sub_dis -> avp_str , ": " ) + 2 ;
 }
 return 4 ;
 }