static int qemuMonitorTextParseBlockJobOne ( const char * text , const char * device , virDomainBlockJobInfoPtr info , const char * * next ) {
 virDomainBlockJobInfo tmp ;
 char * p ;
 unsigned long long speed_bytes ;
 int mismatch = 0 ;
 if ( next == NULL ) return - 1 ;
 * next = NULL ;
 if ( ( text = STRSKIP ( text , "Streaming device " ) ) == NULL ) return - EINVAL ;
 if ( ! STREQLEN ( text , device , strlen ( device ) ) ) mismatch = 1 ;
 if ( ( text = strstr ( text , ": Completed " ) ) == NULL ) return - EINVAL ;
 text += 11 ;
 if ( virStrToLong_ull ( text , & p , 10 , & tmp . cur ) ) return - EINVAL ;
 text = p ;
 if ( ! STRPREFIX ( text , " of " ) ) return - EINVAL ;
 text += 4 ;
 if ( virStrToLong_ull ( text , & p , 10 , & tmp . end ) ) return - EINVAL ;
 text = p ;
 if ( ! STRPREFIX ( text , " bytes, speed limit " ) ) return - EINVAL ;
 text += 20 ;
 if ( virStrToLong_ull ( text , & p , 10 , & speed_bytes ) ) return - EINVAL ;
 text = p ;
 if ( ! STRPREFIX ( text , " bytes/s" ) ) return - EINVAL ;
 if ( mismatch ) {
 * next = STRSKIP ( text , "\n" ) ;
 return - EAGAIN ;
 }
 if ( info ) {
 info -> cur = tmp . cur ;
 info -> end = tmp . end ;
 info -> bandwidth = speed_bytes / 1024ULL / 1024ULL ;
 info -> type = VIR_DOMAIN_BLOCK_JOB_TYPE_PULL ;
 }
 return 1 ;
 }