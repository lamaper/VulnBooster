static int fetch_indices ( void ) {
 int ret ;
 if ( push_verbosely ) fprintf ( stderr , "Getting pack list\n" ) ;
 switch ( http_get_info_packs ( repo -> url , & repo -> packs ) ) {
 case HTTP_OK : case HTTP_MISSING_TARGET : ret = 0 ;
 break ;
 default : ret = - 1 ;
 }
 return ret ;
 }