int BIO_vsnprintf ( char * buf , size_t n , const char * format , va_list args ) {
 size_t retlen ;
 int truncated ;
 _dopr ( & buf , NULL , & n , & retlen , & truncated , format , args ) ;
 if ( truncated ) return - 1 ;
 else return ( retlen <= INT_MAX ) ? ( int ) retlen : - 1 ;
 }