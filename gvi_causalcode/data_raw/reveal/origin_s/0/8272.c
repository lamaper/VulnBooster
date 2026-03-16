static void dequant ( TwinContext * tctx , GetBitContext * gb , float * out , enum FrameType ftype , const int16_t * cb0 , const int16_t * cb1 , int cb_len ) {
 int pos = 0 ;
 int i , j ;
 for ( i = 0 ;
 i < tctx -> n_div [ ftype ] ;
 i ++ ) {
 int tmp0 , tmp1 ;
 int sign0 = 1 ;
 int sign1 = 1 ;
 const int16_t * tab0 , * tab1 ;
 int length = tctx -> length [ ftype ] [ i >= tctx -> length_change [ ftype ] ] ;
 int bitstream_second_part = ( i >= tctx -> bits_main_spec_change [ ftype ] ) ;
 int bits = tctx -> bits_main_spec [ 0 ] [ ftype ] [ bitstream_second_part ] ;
 if ( bits == 7 ) {
 if ( get_bits1 ( gb ) ) sign0 = - 1 ;
 bits = 6 ;
 }
 tmp0 = get_bits ( gb , bits ) ;
 bits = tctx -> bits_main_spec [ 1 ] [ ftype ] [ bitstream_second_part ] ;
 if ( bits == 7 ) {
 if ( get_bits1 ( gb ) ) sign1 = - 1 ;
 bits = 6 ;
 }
 tmp1 = get_bits ( gb , bits ) ;
 tab0 = cb0 + tmp0 * cb_len ;
 tab1 = cb1 + tmp1 * cb_len ;
 for ( j = 0 ;
 j < length ;
 j ++ ) out [ tctx -> permut [ ftype ] [ pos + j ] ] = sign0 * tab0 [ j ] + sign1 * tab1 [ j ] ;
 pos += length ;
 }
 }