static char * strdate ( krb5_timestamp when ) {
 struct tm * tm ;
 static char out [ 40 ] ;
 time_t lcltim = when ;
 tm = localtime ( & lcltim ) ;
 strftime ( out , sizeof ( out ) , "%a %b %d %H:%M:%S %Z %Y" , tm ) ;
 return out ;
 }