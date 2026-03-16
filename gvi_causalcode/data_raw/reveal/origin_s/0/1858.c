static void _dumpcffstrings ( FILE * file , struct pschars * strs ) {
 int i , len , offsize ;
 len = 1 ;
 for ( i = 0 ;
 i < strs -> next ;
 ++ i ) len += strs -> lens [ i ] ;
 putshort ( file , strs -> next ) ;
 if ( strs -> next != 0 ) {
 offsize = len <= 255 ? 1 : len <= 65535 ? 2 : len <= 0xffffff ? 3 : 4 ;
 putc ( offsize , file ) ;
 len = 1 ;
 for ( i = 0 ;
 i < strs -> next ;
 ++ i ) {
 dumpoffset ( file , offsize , len ) ;
 len += strs -> lens [ i ] ;
 }
 dumpoffset ( file , offsize , len ) ;
 for ( i = 0 ;
 i < strs -> next ;
 ++ i ) {
 uint8 * pt = strs -> values [ i ] , * end = pt + strs -> lens [ i ] ;
 while ( pt < end ) {
 putc ( * pt ++ , file ) ;
 }
 }
 }
 }