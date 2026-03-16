int MBS_ApplyPatch ( const MBSPatchHeader * header , int patchfd , unsigned char * fbuffer , int filefd ) {
 unsigned char * fbufend = fbuffer + header -> slen ;
 unsigned char * buf = ( unsigned char * ) malloc ( header -> cblen + header -> difflen + header -> extralen ) ;
 if ( ! buf ) return MEM_ERROR ;
 int rv = OK ;
 int r = header -> cblen + header -> difflen + header -> extralen ;
 unsigned char * wb = buf ;
 while ( r ) {
 int c = read ( patchfd , wb , ( r > SSIZE_MAX ) ? SSIZE_MAX : r ) ;
 if ( c < 0 ) {
 rv = READ_ERROR ;
 goto end ;
 }
 r -= c ;
 if ( c == 0 && r ) {
 rv = UNEXPECTED_ERROR ;
 goto end ;
 }
 }
 {
 MBSPatchTriple * ctrlsrc = ( MBSPatchTriple * ) buf ;
 unsigned char * diffsrc = buf + header -> cblen ;
 unsigned char * extrasrc = diffsrc + header -> difflen ;
 MBSPatchTriple * ctrlend = ( MBSPatchTriple * ) diffsrc ;
 unsigned char * diffend = extrasrc ;
 unsigned char * extraend = extrasrc + header -> extralen ;
 do {
 ctrlsrc -> x = ntohl ( ctrlsrc -> x ) ;
 ctrlsrc -> y = ntohl ( ctrlsrc -> y ) ;
 ctrlsrc -> z = ntohl ( ctrlsrc -> z ) ;


 rv = UNEXPECTED_ERROR ;
 goto end ;
 }
 for ( unsigned int i = 0 ;
 i < ctrlsrc -> x ;
 ++ i ) {
 diffsrc [ i ] += fbuffer [ i ] ;
 }
 if ( ( int ) write ( filefd , diffsrc , ctrlsrc -> x ) != ctrlsrc -> x ) {
 rv = WRITE_ERROR ;
 goto end ;
 }
 fbuffer += ctrlsrc -> x ;
 diffsrc += ctrlsrc -> x ;
 if ( extrasrc + ctrlsrc -> y > extraend ) {
 rv = UNEXPECTED_ERROR ;
 goto end ;
 }
 if ( ( int ) write ( filefd , extrasrc , ctrlsrc -> y ) != ctrlsrc -> y ) {
 rv = WRITE_ERROR ;
 goto end ;
 }
 extrasrc += ctrlsrc -> y ;
 if ( fbuffer + ctrlsrc -> z > fbufend ) {
 rv = UNEXPECTED_ERROR ;
 goto end ;
 }
 fbuffer += ctrlsrc -> z ;
 ++ ctrlsrc ;
 }
 while ( ctrlsrc < ctrlend ) ;
 }
 end : free ( buf ) ;
 return rv ;
 }