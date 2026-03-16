static int read_frame ( struct VpxDecInputContext * input , uint8_t * * buf , size_t * bytes_in_buffer , size_t * buffer_size ) {
 switch ( input -> vpx_input_ctx -> file_type ) {


 case FILE_TYPE_IVF : return ivf_read_frame ( input -> vpx_input_ctx -> file , buf , bytes_in_buffer , buffer_size ) ;
 default : return 1 ;
 }
 }