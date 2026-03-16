static int xmlLinkCompare ( const void * data0 , const void * data1 ) {
 if ( data0 < data1 ) return ( - 1 ) ;
 else if ( data0 == data1 ) return ( 0 ) ;
 return ( 1 ) ;
 }