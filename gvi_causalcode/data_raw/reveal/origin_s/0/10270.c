static hb_bool_t _try_make_writable_inplace_unix ( hb_blob_t * blob ) {

 const char * addr ;




 DEBUG_MSG_FUNC ( BLOB , blob , "failed to get pagesize: %s" , strerror ( errno ) ) ;
 return false ;
 }
 DEBUG_MSG_FUNC ( BLOB , blob , "pagesize is %lu" , ( unsigned long ) pagesize ) ;
 mask = ~ ( pagesize - 1 ) ;
 addr = ( const char * ) ( ( ( uintptr_t ) blob -> data ) & mask ) ;
 length = ( const char * ) ( ( ( uintptr_t ) blob -> data + blob -> length + pagesize - 1 ) & mask ) - addr ;
 DEBUG_MSG_FUNC ( BLOB , blob , "calling mprotect on [%p..%p] (%lu bytes)" , addr , addr + length , ( unsigned long ) length ) ;
 if ( - 1 == mprotect ( ( void * ) addr , length , PROT_READ | PROT_WRITE ) ) {
 DEBUG_MSG_FUNC ( BLOB , blob , "mprotect failed: %s" , strerror ( errno ) ) ;
 return false ;
 }
 blob -> mode = HB_MEMORY_MODE_WRITABLE ;
 DEBUG_MSG_FUNC ( BLOB , blob , "successfully made [%p..%p] (%lu bytes) writable\n" , addr , addr + length , ( unsigned long ) length ) ;
 return true ;

