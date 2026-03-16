static void dissect_diameter_other_vendor_exp_res ( tvbuff_t * tvb , proto_tree * tree , diam_sub_dis_t * diam_sub_dis ) {
 proto_item * pi ;
 if ( tree ) {
 pi = proto_tree_add_item ( tree , hf_diameter_other_vendor_exp_res , tvb , 0 , 4 , ENC_BIG_ENDIAN ) ;
 diam_sub_dis -> avp_str = ( char * ) wmem_alloc ( wmem_packet_scope ( ) , ITEM_LABEL_LENGTH + 1 ) ;
 proto_item_fill_label ( PITEM_FINFO ( pi ) , diam_sub_dis -> avp_str ) ;
 diam_sub_dis -> avp_str = strstr ( diam_sub_dis -> avp_str , ": " ) + 2 ;
 }
 }