static void print_blob_as_hex ( FILE * output_file , const char * str , ulong len ) {
 const char * ptr = str , * end = ptr + len ;
 for ( ;
 ptr < end ;
 ptr ++ ) fprintf ( output_file , "%02X" , * ( ( uchar * ) ptr ) ) ;
 check_io ( output_file ) ;
 }