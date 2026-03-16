extern int main ( int argc , const char * argv [ ] ) {
 UNewDataMemory * pData ;
 UErrorCode errorCode = U_ZERO_ERROR ;
 char stringValue [ ] = {
 'E' , 'X' , 'A' , 'M' , 'P' , 'L' , 'E' , '\0' }
 ;
 uint16_t intValue = 2000 ;
 long dataLength ;
 uint32_t size ;



 if ( currdir != NULL ) {
 free ( currdir ) ;
 }
 if ( U_FAILURE ( errorCode ) ) {
 fprintf ( stderr , "Error: unable to create data memory, error %d\n" , errorCode ) ;
 exit ( errorCode ) ;
 }
 printf ( "Writing uint16_t value of %d\n" , intValue ) ;
 udata_write16 ( pData , intValue ) ;
 printf ( "Writing string value of %s\n" , stringValue ) ;
 udata_writeString ( pData , stringValue , sizeof ( stringValue ) ) ;
 dataLength = udata_finish ( pData , & errorCode ) ;
 if ( U_FAILURE ( errorCode ) ) {
 fprintf ( stderr , "Error: error %d writing the output file\n" , errorCode ) ;
 exit ( errorCode ) ;
 }
 size = sizeof ( stringValue ) + sizeof ( intValue ) ;
 if ( dataLength != ( long ) size ) {
 fprintf ( stderr , "Error: data length %ld != calculated size %lu\n" , dataLength , size ) ;
 exit ( U_INTERNAL_PROGRAM_ERROR ) ;
 }
 return 0 ;
 }