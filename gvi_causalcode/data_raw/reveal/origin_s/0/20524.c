int ReadInt ( ArchiveHandle * AH ) {
 int res = 0 ;
 int bv , b ;
 int sign = 0 ;
 int bitShift = 0 ;
 if ( AH -> version > K_VERS_1_0 ) sign = ( * AH -> ReadBytePtr ) ( AH ) ;
 for ( b = 0 ;
 b < AH -> intSize ;
 b ++ ) {
 bv = ( * AH -> ReadBytePtr ) ( AH ) & 0xFF ;
 if ( bv != 0 ) res = res + ( bv << bitShift ) ;
 bitShift += 8 ;
 }
 if ( sign ) res = - res ;
 return res ;
 }