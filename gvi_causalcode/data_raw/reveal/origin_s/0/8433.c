static int decorrelate ( TAKDecContext * s , int c1 , int c2 , int length ) {
 GetBitContext * gb = & s -> gb ;
 int32_t * p1 = s -> decoded [ c1 ] + 1 ;
 int32_t * p2 = s -> decoded [ c2 ] + 1 ;
 int i ;
 int dshift , dfactor ;
 switch ( s -> dmode ) {
 case 1 : for ( i = 0 ;
 i < length ;
 i ++ ) {
 int32_t a = p1 [ i ] ;
 int32_t b = p2 [ i ] ;
 p2 [ i ] = a + b ;
 }
 break ;
 case 2 : for ( i = 0 ;
 i < length ;
 i ++ ) {
 int32_t a = p1 [ i ] ;
 int32_t b = p2 [ i ] ;
 p1 [ i ] = b - a ;
 }
 break ;
 case 3 : for ( i = 0 ;
 i < length ;
 i ++ ) {
 int32_t a = p1 [ i ] ;
 int32_t b = p2 [ i ] ;
 a -= b >> 1 ;
 p1 [ i ] = a ;
 p2 [ i ] = a + b ;
 }
 break ;
 case 4 : FFSWAP ( int32_t * , p1 , p2 ) ;
 case 5 : dshift = get_bits_esc4 ( gb ) ;
 dfactor = get_sbits ( gb , 10 ) ;
 for ( i = 0 ;
 i < length ;
 i ++ ) {
 int32_t a = p1 [ i ] ;
 int32_t b = p2 [ i ] ;
 b = dfactor * ( b >> dshift ) + 128 >> 8 << dshift ;
 p1 [ i ] = b - a ;
 }
 break ;
 case 6 : FFSWAP ( int32_t * , p1 , p2 ) ;
 case 7 : {
 LOCAL_ALIGNED_16 ( int16_t , filter , [ MAX_PREDICTORS ] ) ;
 int length2 , order_half , filter_order , dval1 , dval2 ;
 int av_uninit ( code_size ) ;
 memset ( filter , 0 , MAX_PREDICTORS * sizeof ( * filter ) ) ;
 if ( length < 256 ) return AVERROR_INVALIDDATA ;
 dshift = get_bits_esc4 ( gb ) ;
 filter_order = 8 << get_bits1 ( gb ) ;
 dval1 = get_bits1 ( gb ) ;
 dval2 = get_bits1 ( gb ) ;
 for ( i = 0 ;
 i < filter_order ;
 i ++ ) {
 if ( ! ( i & 3 ) ) code_size = 14 - get_bits ( gb , 3 ) ;
 filter [ i ] = get_sbits ( gb , code_size ) ;
 }
 order_half = filter_order / 2 ;
 length2 = length - ( filter_order - 1 ) ;
 if ( dval1 ) {
 for ( i = 0 ;
 i < order_half ;
 i ++ ) {
 int32_t a = p1 [ i ] ;
 int32_t b = p2 [ i ] ;
 p1 [ i ] = a + b ;
 }
 }
 if ( dval2 ) {
 for ( i = length2 + order_half ;
 i < length ;
 i ++ ) {
 int32_t a = p1 [ i ] ;
 int32_t b = p2 [ i ] ;
 p1 [ i ] = a + b ;
 }
 }
 av_fast_malloc ( & s -> residues , & s -> residues_buf_size , FFALIGN ( length + 16 , 16 ) * sizeof ( * s -> residues ) ) ;
 if ( ! s -> residues ) return AVERROR ( ENOMEM ) ;
 memset ( s -> residues , 0 , s -> residues_buf_size ) ;
 for ( i = 0 ;
 i < length ;
 i ++ ) s -> residues [ i ] = p2 [ i ] >> dshift ;
 p1 += order_half ;
 for ( i = 0 ;
 i < length2 ;
 i ++ ) {
 int v = 1 << 9 ;
 v += s -> dsp . scalarproduct_int16 ( & s -> residues [ i ] , filter , FFALIGN ( filter_order , 16 ) ) ;
 p1 [ i ] = ( av_clip ( v >> 10 , - 8192 , 8191 ) << dshift ) - p1 [ i ] ;
 }
 emms_c ( ) ;
 break ;
 }
 }
 return 0 ;
 }