static gchar * qio_channel_websock_date_str ( void ) {
 struct tm tm ;
 time_t now = time ( NULL ) ;
 char datebuf [ 128 ] ;
 gmtime_r ( & now , & tm ) ;
 strftime ( datebuf , sizeof ( datebuf ) , "%a, %d %b %Y %H:%M:%S GMT" , & tm ) ;
 return g_strdup ( datebuf ) ;
 }