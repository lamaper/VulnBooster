static StemInfo * SameH ( StemInfo * old , real start , real width , real unblended [ 2 ] [ MmMax ] , int instance_count ) {
 StemInfo * sameh ;
 if ( instance_count == 0 ) {
 for ( sameh = old ;
 sameh != NULL ;
 sameh = sameh -> next ) if ( sameh -> start == start && sameh -> width == width ) break ;
 }
 else {
 int j ;
 for ( j = 1 ;
 j < instance_count ;
 ++ j ) {
 unblended [ 0 ] [ j ] += unblended [ 0 ] [ j - 1 ] ;
 unblended [ 1 ] [ j ] += unblended [ 1 ] [ j - 1 ] ;
 }
 for ( sameh = old ;
 sameh != NULL ;
 sameh = sameh -> next ) {
 if ( ( * sameh -> u . unblended ) [ 0 ] == NULL || ( * sameh -> u . unblended ) [ 1 ] == NULL ) continue ;
 if ( UnblendedCompare ( ( * sameh -> u . unblended ) [ 0 ] , unblended [ 0 ] , instance_count ) == 0 && UnblendedCompare ( ( * sameh -> u . unblended ) [ 1 ] , unblended [ 1 ] , instance_count ) == 0 ) break ;
 }
 }
 return ( sameh ) ;
 }