static void evhttp_maybe_add_date_header ( struct evkeyvalq * headers ) {
 if ( evhttp_find_header ( headers , "Date" ) == NULL ) {
 char date [ 50 ] ;


 time_t t = time ( NULL ) ;


 cur_p = & cur ;

 evhttp_add_header ( headers , "Date" , date ) ;
 }
 }
 }