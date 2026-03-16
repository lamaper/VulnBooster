static void * img_buf_memalign ( size_t align , size_t size ) {
 void * addr , * x = NULL ;
 addr = malloc ( size + align - 1 + ADDRESS_STORAGE_SIZE ) ;
 if ( addr ) {
 x = align_addr ( ( unsigned char * ) addr + ADDRESS_STORAGE_SIZE , ( int ) align ) ;
 ( ( size_t * ) x ) [ - 1 ] = ( size_t ) addr ;
 }
 return x ;
 }