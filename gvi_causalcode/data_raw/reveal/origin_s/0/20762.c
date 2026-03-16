static int compare_avps ( const void * a , const void * b ) {
 const value_string * vsa = ( const value_string * ) a ;
 const value_string * vsb = ( const value_string * ) b ;
 if ( vsa -> value > vsb -> value ) return 1 ;
 if ( vsa -> value < vsb -> value ) return - 1 ;
 return 0 ;
 }