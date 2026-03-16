static void stream_add_data ( struct attachment_istream * astream , const void * data , size_t size ) {
 if ( size > 0 ) {
 memcpy ( i_stream_alloc ( & astream -> istream , size ) , data , size ) ;
 astream -> istream . pos += size ;
 }
 }