void getauthkeys ( const char * keyfile ) {
 int len ;
 len = strlen ( keyfile ) ;
 if ( ! len ) return ;

 memcpy ( key_file_name , keyfile , len + 1 ) ;

 if ( len + 1 > _MAX_PATH ) return ;
 if ( ! ExpandEnvironmentStrings ( keyfile , key_file_name , _MAX_PATH ) ) {
 msyslog ( LOG_ERR , "ExpandEnvironmentStrings(KEY_FILE) failed: %m" ) ;
 strncpy ( key_file_name , keyfile , _MAX_PATH ) ;
 }

 }