static int vc1_decode_i_block ( VC1Context * v , int16_t block [ 64 ] , int n , int coded , int codingset ) {
 GetBitContext * gb = & v -> s . gb ;
 MpegEncContext * s = & v -> s ;
 int dc_pred_dir = 0 ;
 int i ;
 int16_t * dc_val ;
 int16_t * ac_val , * ac_val2 ;
 int dcdiff ;
 if ( n < 4 ) {
 dcdiff = get_vlc2 ( & s -> gb , ff_msmp4_dc_luma_vlc [ s -> dc_table_index ] . table , DC_VLC_BITS , 3 ) ;
 }
 else {
 dcdiff = get_vlc2 ( & s -> gb , ff_msmp4_dc_chroma_vlc [ s -> dc_table_index ] . table , DC_VLC_BITS , 3 ) ;
 }
 if ( dcdiff < 0 ) {
 av_log ( s -> avctx , AV_LOG_ERROR , "Illegal DC VLC\n" ) ;
 return - 1 ;
 }
 if ( dcdiff ) {
 if ( dcdiff == 119 ) {
 if ( v -> pq == 1 ) dcdiff = get_bits ( gb , 10 ) ;
 else if ( v -> pq == 2 ) dcdiff = get_bits ( gb , 9 ) ;
 else dcdiff = get_bits ( gb , 8 ) ;
 }
 else {
 if ( v -> pq == 1 ) dcdiff = ( dcdiff << 2 ) + get_bits ( gb , 2 ) - 3 ;
 else if ( v -> pq == 2 ) dcdiff = ( dcdiff << 1 ) + get_bits1 ( gb ) - 1 ;
 }
 if ( get_bits1 ( gb ) ) dcdiff = - dcdiff ;
 }
 dcdiff += vc1_i_pred_dc ( & v -> s , v -> overlap , v -> pq , n , & dc_val , & dc_pred_dir ) ;
 * dc_val = dcdiff ;
 if ( n < 4 ) {
 block [ 0 ] = dcdiff * s -> y_dc_scale ;
 }
 else {
 block [ 0 ] = dcdiff * s -> c_dc_scale ;
 }
 if ( ! coded ) {
 goto not_coded ;
 }
 i = 1 ;
 {
 int last = 0 , skip , value ;
 const uint8_t * zz_table ;
 int scale ;
 int k ;
 scale = v -> pq * 2 + v -> halfpq ;
 if ( v -> s . ac_pred ) {
 if ( ! dc_pred_dir ) zz_table = v -> zz_8x8 [ 2 ] ;
 else zz_table = v -> zz_8x8 [ 3 ] ;
 }
 else zz_table = v -> zz_8x8 [ 1 ] ;
 ac_val = s -> ac_val [ 0 ] [ 0 ] + s -> block_index [ n ] * 16 ;
 ac_val2 = ac_val ;
 if ( dc_pred_dir ) ac_val -= 16 ;
 else ac_val -= 16 * s -> block_wrap [ n ] ;
 while ( ! last ) {
 vc1_decode_ac_coeff ( v , & last , & skip , & value , codingset ) ;
 i += skip ;
 if ( i > 63 ) break ;
 block [ zz_table [ i ++ ] ] = value ;
 }
 if ( s -> ac_pred ) {
 if ( dc_pred_dir ) {
 for ( k = 1 ;
 k < 8 ;
 k ++ ) block [ k << v -> left_blk_sh ] += ac_val [ k ] ;
 }
 else {
 for ( k = 1 ;
 k < 8 ;
 k ++ ) block [ k << v -> top_blk_sh ] += ac_val [ k + 8 ] ;
 }
 }
 for ( k = 1 ;
 k < 8 ;
 k ++ ) {
 ac_val2 [ k ] = block [ k << v -> left_blk_sh ] ;
 ac_val2 [ k + 8 ] = block [ k << v -> top_blk_sh ] ;
 }
 for ( k = 1 ;
 k < 64 ;
 k ++ ) if ( block [ k ] ) {
 block [ k ] *= scale ;
 if ( ! v -> pquantizer ) block [ k ] += ( block [ k ] < 0 ) ? - v -> pq : v -> pq ;
 }
 if ( s -> ac_pred ) i = 63 ;
 }
 not_coded : if ( ! coded ) {
 int k , scale ;
 ac_val = s -> ac_val [ 0 ] [ 0 ] + s -> block_index [ n ] * 16 ;
 ac_val2 = ac_val ;
 i = 0 ;
 scale = v -> pq * 2 + v -> halfpq ;
 memset ( ac_val2 , 0 , 16 * 2 ) ;
 if ( dc_pred_dir ) {
 ac_val -= 16 ;
 if ( s -> ac_pred ) memcpy ( ac_val2 , ac_val , 8 * 2 ) ;
 }
 else {
 ac_val -= 16 * s -> block_wrap [ n ] ;
 if ( s -> ac_pred ) memcpy ( ac_val2 + 8 , ac_val + 8 , 8 * 2 ) ;
 }
 if ( s -> ac_pred ) {
 if ( dc_pred_dir ) {
 for ( k = 1 ;
 k < 8 ;
 k ++ ) {
 block [ k << v -> left_blk_sh ] = ac_val [ k ] * scale ;
 if ( ! v -> pquantizer && block [ k << v -> left_blk_sh ] ) block [ k << v -> left_blk_sh ] += ( block [ k << v -> left_blk_sh ] < 0 ) ? - v -> pq : v -> pq ;
 }
 }
 else {
 for ( k = 1 ;
 k < 8 ;
 k ++ ) {
 block [ k << v -> top_blk_sh ] = ac_val [ k + 8 ] * scale ;
 if ( ! v -> pquantizer && block [ k << v -> top_blk_sh ] ) block [ k << v -> top_blk_sh ] += ( block [ k << v -> top_blk_sh ] < 0 ) ? - v -> pq : v -> pq ;
 }
 }
 i = 63 ;
 }
 }
 s -> block_last_index [ n ] = i ;
 return 0 ;
 }