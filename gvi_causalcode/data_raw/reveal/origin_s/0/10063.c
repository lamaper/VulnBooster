static struct vp9_read_bit_buffer * init_read_bit_buffer ( VP9Decoder * pbi , struct vp9_read_bit_buffer * rb , const uint8_t * data , const uint8_t * data_end , uint8_t * clear_data ) {
 rb -> bit_offset = 0 ;
 rb -> error_handler = error_handler ;
 rb -> error_handler_data = & pbi -> common ;
 if ( pbi -> decrypt_cb ) {
 const int n = ( int ) MIN ( MAX_VP9_HEADER_SIZE , data_end - data ) ;
 pbi -> decrypt_cb ( pbi -> decrypt_state , data , clear_data , n ) ;
 rb -> bit_buffer = clear_data ;
 rb -> bit_buffer_end = clear_data + n ;
 }
 else {
 rb -> bit_buffer = data ;
 rb -> bit_buffer_end = data_end ;
 }
 return rb ;
 }