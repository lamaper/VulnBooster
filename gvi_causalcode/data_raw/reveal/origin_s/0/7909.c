static void build_nmv_component_cost_table ( int * mvcost , const nmv_component * const mvcomp , int usehp ) {
 int i , v ;
 int sign_cost [ 2 ] , class_cost [ MV_CLASSES ] , class0_cost [ CLASS0_SIZE ] ;
 int bits_cost [ MV_OFFSET_BITS ] [ 2 ] ;
 int class0_fp_cost [ CLASS0_SIZE ] [ MV_FP_SIZE ] , fp_cost [ MV_FP_SIZE ] ;
 int class0_hp_cost [ 2 ] , hp_cost [ 2 ] ;
 sign_cost [ 0 ] = vp9_cost_zero ( mvcomp -> sign ) ;
 sign_cost [ 1 ] = vp9_cost_one ( mvcomp -> sign ) ;
 vp9_cost_tokens ( class_cost , mvcomp -> classes , vp9_mv_class_tree ) ;
 vp9_cost_tokens ( class0_cost , mvcomp -> class0 , vp9_mv_class0_tree ) ;
 for ( i = 0 ;
 i < MV_OFFSET_BITS ;
 ++ i ) {
 bits_cost [ i ] [ 0 ] = vp9_cost_zero ( mvcomp -> bits [ i ] ) ;
 bits_cost [ i ] [ 1 ] = vp9_cost_one ( mvcomp -> bits [ i ] ) ;
 }
 for ( i = 0 ;
 i < CLASS0_SIZE ;
 ++ i ) vp9_cost_tokens ( class0_fp_cost [ i ] , mvcomp -> class0_fp [ i ] , vp9_mv_fp_tree ) ;
 vp9_cost_tokens ( fp_cost , mvcomp -> fp , vp9_mv_fp_tree ) ;
 if ( usehp ) {
 class0_hp_cost [ 0 ] = vp9_cost_zero ( mvcomp -> class0_hp ) ;
 class0_hp_cost [ 1 ] = vp9_cost_one ( mvcomp -> class0_hp ) ;
 hp_cost [ 0 ] = vp9_cost_zero ( mvcomp -> hp ) ;
 hp_cost [ 1 ] = vp9_cost_one ( mvcomp -> hp ) ;
 }
 mvcost [ 0 ] = 0 ;
 for ( v = 1 ;
 v <= MV_MAX ;
 ++ v ) {
 int z , c , o , d , e , f , cost = 0 ;
 z = v - 1 ;
 c = vp9_get_mv_class ( z , & o ) ;
 cost += class_cost [ c ] ;
 d = ( o >> 3 ) ;
 f = ( o >> 1 ) & 3 ;
 e = ( o & 1 ) ;
 if ( c == MV_CLASS_0 ) {
 cost += class0_cost [ d ] ;
 }
 else {
 int i , b ;
 b = c + CLASS0_BITS - 1 ;
 for ( i = 0 ;
 i < b ;
 ++ i ) cost += bits_cost [ i ] [ ( ( d >> i ) & 1 ) ] ;
 }
 if ( c == MV_CLASS_0 ) {
 cost += class0_fp_cost [ d ] [ f ] ;
 }
 else {
 cost += fp_cost [ f ] ;
 }
 if ( usehp ) {
 if ( c == MV_CLASS_0 ) {
 cost += class0_hp_cost [ e ] ;
 }
 else {
 cost += hp_cost [ e ] ;
 }
 }
 mvcost [ v ] = cost + sign_cost [ 0 ] ;
 mvcost [ - v ] = cost + sign_cost [ 1 ] ;
 }
 }