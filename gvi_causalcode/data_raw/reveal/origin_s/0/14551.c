size_t WriteInt ( ArchiveHandle * AH , int i ) {
 int b ;
 if ( i < 0 ) {
 ( * AH -> WriteBytePtr ) ( AH , 1 ) ;
 i = - i ;
 }
 else ( * AH -> WriteBytePtr ) ( AH , 0 ) ;
 for ( b = 0 ;
 b < AH -> intSize ;
 b ++ ) {
 ( * AH -> WriteBytePtr ) ( AH , i & 0xFF ) ;
 i >>= 8 ;
 }
 return AH -> intSize + 1 ;
 }