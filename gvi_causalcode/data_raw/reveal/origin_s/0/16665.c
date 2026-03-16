size_t WriteOffset ( ArchiveHandle * AH , pgoff_t o , int wasSet ) {
 int off ;
 ( * AH -> WriteBytePtr ) ( AH , wasSet ) ;
 for ( off = 0 ;
 off < sizeof ( pgoff_t ) ;
 off ++ ) {
 ( * AH -> WriteBytePtr ) ( AH , o & 0xFF ) ;
 o >>= 8 ;
 }
 return sizeof ( pgoff_t ) + 1 ;
 }