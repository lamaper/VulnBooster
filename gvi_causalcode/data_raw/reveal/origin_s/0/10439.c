static unsigned long xmlHashComputeKey ( xmlHashTablePtr table , const xmlChar * name , const xmlChar * name2 , const xmlChar * name3 ) {
 unsigned long value = 0L ;
 char ch ;


 value += 30 * ( * name ) ;
 while ( ( ch = * name ++ ) != 0 ) {
 value = value ^ ( ( value << 5 ) + ( value >> 3 ) + ( unsigned long ) ch ) ;
 }
 }
 value = value ^ ( ( value << 5 ) + ( value >> 3 ) ) ;
 if ( name2 != NULL ) {
 while ( ( ch = * name2 ++ ) != 0 ) {
 value = value ^ ( ( value << 5 ) + ( value >> 3 ) + ( unsigned long ) ch ) ;
 }
 }
 value = value ^ ( ( value << 5 ) + ( value >> 3 ) ) ;
 if ( name3 != NULL ) {
 while ( ( ch = * name3 ++ ) != 0 ) {
 value = value ^ ( ( value << 5 ) + ( value >> 3 ) + ( unsigned long ) ch ) ;
 }
 }
 return ( value % table -> size ) ;
 }