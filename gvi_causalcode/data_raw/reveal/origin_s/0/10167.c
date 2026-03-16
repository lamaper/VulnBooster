static const char * grouped_avp ( diam_ctx_t * c , diam_avp_t * a , tvbuff_t * tvb , diam_sub_dis_t * diam_sub_dis_inf ) {
 int offset = 0 ;
 int len = tvb_reported_length ( tvb ) ;
 proto_item * pi = proto_tree_add_item ( c -> tree , a -> hf_value , tvb , 0 , - 1 , ENC_BIG_ENDIAN ) ;
 proto_tree * pt = c -> tree ;
 c -> tree = proto_item_add_subtree ( pi , a -> ett ) ;
 diam_sub_dis_inf -> dis_gouped = TRUE ;
 while ( offset < len ) {
 offset += dissect_diameter_avp ( c , tvb , offset , diam_sub_dis_inf ) ;
 }
 diam_sub_dis_inf -> vendor_id = 0 ;
 diam_sub_dis_inf -> dis_gouped = FALSE ;
 diam_sub_dis_inf -> avp_str = NULL ;
 c -> tree = pt ;
 return NULL ;
 }