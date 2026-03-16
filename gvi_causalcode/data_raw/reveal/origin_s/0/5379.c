static int file_read ( void * buf , size_t size , FILE * file ) {
 const int kMaxRetries = 5 ;
 int retry_count = 0 ;
 int file_error ;
 size_t len = 0 ;
 do {
 const size_t n = fread ( ( uint8_t * ) buf + len , 1 , size - len , file ) ;
 len += n ;
 file_error = ferror ( file ) ;
 if ( file_error ) {
 if ( errno == EINTR || errno == EAGAIN ) {
 clearerr ( file ) ;
 continue ;
 }
 else {
 fprintf ( stderr , "Error reading file: %u of %u bytes read, %d: %s\n" , ( uint32_t ) len , ( uint32_t ) size , errno , strerror ( errno ) ) ;
 return 0 ;
 }
 }
 }
 while ( ! feof ( file ) && len < size && ++ retry_count < kMaxRetries ) ;
 if ( ! feof ( file ) && len != size ) {
 fprintf ( stderr , "Error reading file: %u of %u bytes read," " error: %d, retries: %d, %d: %s\n" , ( uint32_t ) len , ( uint32_t ) size , file_error , retry_count , errno , strerror ( errno ) ) ;
 }
 return len == size ;
 }