static void get_tile_buffer ( const uint8_t * const data_end , int is_last , struct vpx_internal_error_info * error_info , const uint8_t * * data , vpx_decrypt_cb decrypt_cb , void * decrypt_state , TileBuffer * buf ) {
 size_t size ;
 if ( ! is_last ) {
 if ( ! read_is_valid ( * data , 4 , data_end ) ) vpx_internal_error ( error_info , VPX_CODEC_CORRUPT_FRAME , "Truncated packet or corrupt tile length" ) ;
 if ( decrypt_cb ) {
 uint8_t be_data [ 4 ] ;
 decrypt_cb ( decrypt_state , * data , be_data , 4 ) ;
 size = mem_get_be32 ( be_data ) ;
 }
 else {
 size = mem_get_be32 ( * data ) ;
 }
 * data += 4 ;
 if ( size > ( size_t ) ( data_end - * data ) ) vpx_internal_error ( error_info , VPX_CODEC_CORRUPT_FRAME , "Truncated packet or corrupt tile size" ) ;
 }
 else {
 size = data_end - * data ;
 }
 buf -> data = * data ;
 buf -> size = size ;
 * data += size ;
 }