void ahwrite ( const void * ptr , size_t size , size_t nmemb , ArchiveHandle * AH ) {
 int bytes_written = 0 ;
 if ( AH -> writingBlob ) {
 size_t remaining = size * nmemb ;
 while ( AH -> lo_buf_used + remaining > AH -> lo_buf_size ) {
 size_t avail = AH -> lo_buf_size - AH -> lo_buf_used ;
 memcpy ( ( char * ) AH -> lo_buf + AH -> lo_buf_used , ptr , avail ) ;
 ptr = ( const void * ) ( ( const char * ) ptr + avail ) ;
 remaining -= avail ;
 AH -> lo_buf_used += avail ;
 dump_lo_buf ( AH ) ;
 }
 memcpy ( ( char * ) AH -> lo_buf + AH -> lo_buf_used , ptr , remaining ) ;
 AH -> lo_buf_used += remaining ;
 bytes_written = size * nmemb ;
 }
 else if ( AH -> gzOut ) bytes_written = GZWRITE ( ptr , size , nmemb , AH -> OF ) ;
 else if ( AH -> CustomOutPtr ) bytes_written = AH -> CustomOutPtr ( AH , ptr , size * nmemb ) ;
 else {
 if ( RestoringToDB ( AH ) ) bytes_written = ExecuteSqlCommandBuf ( & AH -> public , ( const char * ) ptr , size * nmemb ) ;
 else bytes_written = fwrite ( ptr , size , nmemb , AH -> OF ) * size ;
 }
 if ( bytes_written != size * nmemb ) WRITE_ERROR_EXIT ;
 return ;
 }