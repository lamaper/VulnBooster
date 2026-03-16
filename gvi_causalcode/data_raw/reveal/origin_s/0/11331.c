static int rv30_parse_slice_header ( RV34DecContext * r , GetBitContext * gb , SliceInfo * si ) {
 int mb_bits ;
 int w = r -> s . width , h = r -> s . height ;
 int mb_size ;
 int rpr ;
 memset ( si , 0 , sizeof ( SliceInfo ) ) ;
 if ( get_bits ( gb , 3 ) ) return - 1 ;
 si -> type = get_bits ( gb , 2 ) ;
 if ( si -> type == 1 ) si -> type = 0 ;
 if ( get_bits1 ( gb ) ) return - 1 ;
 si -> quant = get_bits ( gb , 5 ) ;
 skip_bits1 ( gb ) ;
 si -> pts = get_bits ( gb , 13 ) ;
 rpr = get_bits ( gb , r -> rpr ) ;
 if ( rpr ) {
 w = r -> s . avctx -> extradata [ 6 + rpr * 2 ] << 2 ;
 h = r -> s . avctx -> extradata [ 7 + rpr * 2 ] << 2 ;
 }
 si -> width = w ;
 si -> height = h ;
 mb_size = ( ( w + 15 ) >> 4 ) * ( ( h + 15 ) >> 4 ) ;
 mb_bits = ff_rv34_get_start_offset ( gb , mb_size ) ;
 si -> start = get_bits ( gb , mb_bits ) ;
 skip_bits1 ( gb ) ;
 return 0 ;
 }