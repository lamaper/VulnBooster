void input_DecoderDecode ( decoder_t * p_dec , block_t * p_block , bool b_do_pace ) {
 decoder_owner_sys_t * p_owner = p_dec -> p_owner ;
 if ( b_do_pace ) {
 if ( ! p_owner -> b_waiting ) block_FifoPace ( p_owner -> p_fifo , 10 , SIZE_MAX ) ;
 }

 msg_Warn ( p_dec , "decoder/packetizer fifo full (data not " "consumed quickly enough), resetting fifo!" ) ;
 block_FifoEmpty ( p_owner -> p_fifo ) ;
 }
 block_FifoPut ( p_owner -> p_fifo , p_block ) ;
 }