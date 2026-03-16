static FileType get_file_type ( const u_char * filename , unsigned int throttle_rate ) {
 struct stat buf ;
 int ret ;
 ret = pp_cached_file_stat_perform ( pp_stat_cache , ( const char * ) filename , & buf , throttle_rate ) ;
 if ( ret == 0 ) {
 if ( S_ISREG ( buf . st_mode ) ) {
 return FT_FILE ;
 }
 else if ( S_ISDIR ( buf . st_mode ) ) {
 return FT_DIRECTORY ;
 }
 else {
 return FT_OTHER ;
 }
 }
 else {
 return FT_ERROR ;
 }
 }