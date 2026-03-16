static int decode_cabac_mb_ref ( H264Context * h , int list , int n ) {
 int refa = h -> ref_cache [ list ] [ scan8 [ n ] - 1 ] ;
 int refb = h -> ref_cache [ list ] [ scan8 [ n ] - 8 ] ;
 int ref = 0 ;
 int ctx = 0 ;
 if ( h -> slice_type_nos == AV_PICTURE_TYPE_B ) {
 if ( refa > 0 && ! ( h -> direct_cache [ scan8 [ n ] - 1 ] & ( MB_TYPE_DIRECT2 >> 1 ) ) ) ctx ++ ;
 if ( refb > 0 && ! ( h -> direct_cache [ scan8 [ n ] - 8 ] & ( MB_TYPE_DIRECT2 >> 1 ) ) ) ctx += 2 ;
 }
 else {
 if ( refa > 0 ) ctx ++ ;
 if ( refb > 0 ) ctx += 2 ;
 }
 while ( get_cabac ( & h -> cabac , & h -> cabac_state [ 54 + ctx ] ) ) {
 ref ++ ;
 ctx = ( ctx >> 2 ) + 4 ;
 if ( ref >= 32 ) {
 return - 1 ;
 }
 }
 return ref ;
 }