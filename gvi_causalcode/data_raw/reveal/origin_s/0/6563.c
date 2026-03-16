static void close_input_file ( struct VpxInputContext * input ) {
 fclose ( input -> file ) ;
 if ( input -> file_type == FILE_TYPE_Y4M ) y4m_input_close ( & input -> y4m ) ;
 }