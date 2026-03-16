static void dissect_coap_opt_block ( tvbuff_t * tvb , proto_item * head_item , proto_tree * subtree , gint offset , gint opt_length , coap_info * coinfo , coap_common_dissect_t * dissect_hf ) {
 guint8 val = 0 ;
 guint encoded_block_size ;
 guint block_esize ;
 if ( opt_length == 0 ) {
 coinfo -> block_number = 0 ;
 val = 0 ;
 }
 else {
 coinfo -> block_number = coap_get_opt_uint ( tvb , offset , opt_length ) >> 4 ;
 val = tvb_get_guint8 ( tvb , offset + opt_length - 1 ) & 0x0f ;
 }
 proto_tree_add_uint ( subtree , dissect_hf -> hf . opt_block_number , tvb , offset , opt_length , coinfo -> block_number ) ;
 coinfo -> block_mflag = ( val & COAP_BLOCK_MFLAG_MASK ) >> 3 ;
 proto_tree_add_uint ( subtree , dissect_hf -> hf . opt_block_mflag , tvb , offset + opt_length - 1 , 1 , coinfo -> block_mflag ) ;
 encoded_block_size = val & COAP_BLOCK_SIZE_MASK ;
 block_esize = 1 << ( encoded_block_size + 4 ) ;
 proto_tree_add_uint_format ( subtree , dissect_hf -> hf . opt_block_size , tvb , offset + opt_length - 1 , 1 , encoded_block_size , "Block Size: %u (%u encoded)" , block_esize , encoded_block_size ) ;
 proto_item_append_text ( head_item , ": NUM:%u, M:%u, SZX:%u" , coinfo -> block_number , coinfo -> block_mflag , block_esize ) ;
 }