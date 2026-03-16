static int read_mv_component ( vp9_reader * r , const nmv_component * mvcomp , int usehp ) {
 int mag , d , fr , hp ;
 const int sign = vp9_read ( r , mvcomp -> sign ) ;
 const int mv_class = vp9_read_tree ( r , vp9_mv_class_tree , mvcomp -> classes ) ;
 const int class0 = mv_class == MV_CLASS_0 ;
 if ( class0 ) {
 d = vp9_read_tree ( r , vp9_mv_class0_tree , mvcomp -> class0 ) ;
 }
 else {
 int i ;
 const int n = mv_class + CLASS0_BITS - 1 ;
 d = 0 ;
 for ( i = 0 ;
 i < n ;
 ++ i ) d |= vp9_read ( r , mvcomp -> bits [ i ] ) << i ;
 }
 fr = vp9_read_tree ( r , vp9_mv_fp_tree , class0 ? mvcomp -> class0_fp [ d ] : mvcomp -> fp ) ;
 hp = usehp ? vp9_read ( r , class0 ? mvcomp -> class0_hp : mvcomp -> hp ) : 1 ;
 mag = vp9_get_mv_mag ( mv_class , ( d << 3 ) | ( fr << 1 ) | hp ) + 1 ;
 return sign ? - mag : mag ;
 }