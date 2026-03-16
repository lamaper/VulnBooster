static void sbr_hf_g_filt_c ( float ( * Y ) [ 2 ] , const float ( * X_high ) [ 40 ] [ 2 ] , const float * g_filt , int m_max , intptr_t ixh ) {
 int m ;
 for ( m = 0 ;
 m < m_max ;
 m ++ ) {
 Y [ m ] [ 0 ] = X_high [ m ] [ ixh ] [ 0 ] * g_filt [ m ] ;
 Y [ m ] [ 1 ] = X_high [ m ] [ ixh ] [ 1 ] * g_filt [ m ] ;
 }
 }