static void * DecoderThread ( void * p_data ) {
 decoder_t * p_dec = ( decoder_t * ) p_data ;
 decoder_owner_sys_t * p_owner = p_dec -> p_owner ;
 for ( ;
 ;
 ) {
 block_t * p_block = block_FifoGet ( p_owner -> p_fifo ) ;
 bool end_wait = ! p_block || p_block -> i_flags & BLOCK_FLAG_CORE_EOS ;
 DecoderSignalWait ( p_dec , end_wait ) ;
 if ( end_wait ) input_DecoderStopWait ( p_dec ) ;
 if ( p_block ) {
 int canc = vlc_savecancel ( ) ;
 if ( p_block -> i_flags & BLOCK_FLAG_CORE_EOS ) {
 block_Release ( p_block ) ;
 p_block = NULL ;
 }
 DecoderProcess ( p_dec , p_block ) ;
 vlc_restorecancel ( canc ) ;
 }
 }
 return NULL ;
 }