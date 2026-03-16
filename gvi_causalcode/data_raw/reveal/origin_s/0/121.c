guint8 dissect_coap_code ( tvbuff_t * tvb , proto_tree * tree , gint * offset , coap_common_dissect_t * dissect_hf , guint8 * code_class ) {
 guint8 code ;
 proto_tree_add_item ( tree , dissect_hf -> hf . code , tvb , * offset , 1 , ENC_BIG_ENDIAN ) ;
 code = tvb_get_guint8 ( tvb , * offset ) ;
 * code_class = code >> 5 ;
 * offset += 1 ;
 return code ;
 }