static bool has_lock_conflicts ( TocEntry * te1 , TocEntry * te2 ) {
 int j , k ;
 for ( j = 0 ;
 j < te1 -> nLockDeps ;
 j ++ ) {
 for ( k = 0 ;
 k < te2 -> nDeps ;
 k ++ ) {
 if ( te1 -> lockDeps [ j ] == te2 -> dependencies [ k ] ) return true ;
 }
 }
 return false ;
 }