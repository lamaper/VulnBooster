static int grow ( struct evport_data * epdp , int factor ) {
 struct fd_info * tmp ;
 int oldsize = epdp -> ed_nevents ;
 int newsize = factor * oldsize ;
 assert ( factor > 1 ) ;
 check_evportop ( epdp ) ;
 tmp = realloc ( epdp -> ed_fds , sizeof ( struct fd_info ) * newsize ) ;
 if ( NULL == tmp ) return - 1 ;
 epdp -> ed_fds = tmp ;
 memset ( ( char * ) ( epdp -> ed_fds + oldsize ) , 0 , ( newsize - oldsize ) * sizeof ( struct fd_info ) ) ;
 epdp -> ed_nevents = newsize ;
 check_evportop ( epdp ) ;
 return 0 ;
 }