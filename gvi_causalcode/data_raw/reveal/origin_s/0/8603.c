static int endedstopped ( IO * wrapper ) {
 if ( wrapper -> endedstopped ) {
 wrapper -> endedstopped = false ;
 return ( true ) ;
 }
 return ( false ) ;
 }