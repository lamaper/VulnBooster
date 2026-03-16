size_t WriteStr ( ArchiveHandle * AH , const char * c ) {
 size_t res ;
 if ( c ) {
 int len = strlen ( c ) ;
 res = WriteInt ( AH , len ) ;
 ( * AH -> WriteBufPtr ) ( AH , c , len ) ;
 res += len ;
 }
 else res = WriteInt ( AH , - 1 ) ;
 return res ;
 }