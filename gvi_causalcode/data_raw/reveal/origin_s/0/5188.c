static int remote_exists ( const char * path ) {
 char * url = xstrfmt ( "%s%s" , repo -> url , path ) ;
 int ret ;
 switch ( http_get_strbuf ( url , NULL , NULL ) ) {
 case HTTP_OK : ret = 1 ;
 break ;
 case HTTP_MISSING_TARGET : ret = 0 ;
 break ;
 case HTTP_ERROR : error ( "unable to access '%s': %s" , url , curl_errorstr ) ;
 default : ret = - 1 ;
 }
 free ( url ) ;
 return ret ;
 }