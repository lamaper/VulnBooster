static void print_sexp ( const char * prefix , gcry_sexp_t a ) {
 char * buf ;
 size_t size ;
 if ( prefix ) fputs ( prefix , stderr ) ;
 size = gcry_sexp_sprint ( a , GCRYSEXP_FMT_ADVANCED , NULL , 0 ) ;
 buf = gcry_xmalloc ( size ) ;
 gcry_sexp_sprint ( a , GCRYSEXP_FMT_ADVANCED , buf , size ) ;
 fprintf ( stderr , "%.*s" , ( int ) size , buf ) ;
 gcry_free ( buf ) ;
 }