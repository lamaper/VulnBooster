static const chr * scanplain ( struct vars * v ) {
 const chr * endp ;
 assert ( SEE ( COLLEL ) || SEE ( ECLASS ) || SEE ( CCLASS ) ) ;
 NEXT ( ) ;
 endp = v -> now ;
 while ( SEE ( PLAIN ) ) {
 endp = v -> now ;
 NEXT ( ) ;
 }
 assert ( SEE ( END ) || ISERR ( ) ) ;
 NEXT ( ) ;
 return endp ;
 }