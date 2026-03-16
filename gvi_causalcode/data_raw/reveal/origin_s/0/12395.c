void y4m_input_close ( y4m_input * _y4m ) {
 free ( _y4m -> dst_buf ) ;
 free ( _y4m -> aux_buf ) ;
 }