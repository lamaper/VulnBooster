extern int main ( int argc , const char * argv [ ] ) {
 UDataMemory * result = NULL ;
 UErrorCode status = U_ZERO_ERROR ;
 uint16_t intValue = 0 ;
 char * string = NULL ;
 uint16_t * intPointer = NULL ;
 const void * dataMemory = NULL ;
 char curPathBuffer [ 1024 ] ;



 result = udata_openChoice ( curPathBuffer , DATA_TYPE , DATA_NAME , isAcceptable , NULL , & status ) ;
 if ( currdir != NULL ) {
 free ( currdir ) ;
 }
 if ( U_FAILURE ( status ) ) {
 printf ( "Failed to open data file example.dat in %s with error number %d\n" , curPathBuffer , status ) ;
 return - 1 ;
 }
 dataMemory = udata_getMemory ( result ) ;
 intPointer = ( uint16_t * ) dataMemory ;
 printf ( "Read value %d from data file\n" , * intPointer ) ;
 string = ( char * ) ( intPointer + 1 ) ;
 printf ( "Read string %s from data file\n" , string ) ;
 if ( U_SUCCESS ( status ) ) {
 udata_close ( result ) ;
 }
 return 0 ;
 }