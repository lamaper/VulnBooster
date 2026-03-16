static void dissect_q931_ia5_ie ( tvbuff_t * tvb , int offset , int len , proto_tree * tree , int hf_value ) {
 if ( len != 0 ) {
 proto_tree_add_item ( tree , hf_value , tvb , offset , len , ENC_ASCII | ENC_NA ) ;
 proto_item_append_text ( proto_tree_get_parent ( tree ) , " '%s'" , tvb_format_text ( tvb , offset , len ) ) ;
 }
 }