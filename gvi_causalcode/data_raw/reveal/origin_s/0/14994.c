static void dissect_q931_cug_ie ( tvbuff_t * tvb , int offset , int len , proto_tree * tree ) {
 if ( len == 0 ) return ;
 proto_tree_add_item ( tree , hf_q931_cug_indication , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset += 1 ;
 len -= 1 ;
 if ( len == 0 ) return ;
 proto_tree_add_item ( tree , hf_q931_cug_index_code , tvb , offset , len , ENC_NA | ENC_ASCII ) ;
 }