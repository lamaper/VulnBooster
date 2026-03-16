static void setup_token_decoder ( const uint8_t * data , const uint8_t * data_end , size_t read_size , struct vpx_internal_error_info * error_info , vp9_reader * r , vpx_decrypt_cb decrypt_cb , void * decrypt_state ) {
 if ( ! read_is_valid ( data , read_size , data_end ) ) vpx_internal_error ( error_info , VPX_CODEC_CORRUPT_FRAME , "Truncated packet or corrupt tile length" ) ;
 if ( vp9_reader_init ( r , data , read_size , decrypt_cb , decrypt_state ) ) vpx_internal_error ( error_info , VPX_CODEC_MEM_ERROR , "Failed to allocate bool decoder %d" , 1 ) ;
 }