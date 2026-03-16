static inline int wmv2_decode_inter_block ( Wmv2Context * w , int16_t * block , int n , int cbp ) {
 MpegEncContext * const s = & w -> s ;
 static const int sub_cbp_table [ 3 ] = {
 2 , 3 , 1 }
 ;
 int sub_cbp ;
 if ( ! cbp ) {
 s -> block_last_index [ n ] = - 1 ;
 return 0 ;
 }
 if ( w -> per_block_abt ) w -> abt_type = decode012 ( & s -> gb ) ;
 w -> abt_type_table [ n ] = w -> abt_type ;
 if ( w -> abt_type ) {
 const uint8_t * scantable = w -> abt_scantable [ w -> abt_type - 1 ] . scantable ;
 sub_cbp = sub_cbp_table [ decode012 ( & s -> gb ) ] ;
 if ( sub_cbp & 1 ) {
 if ( ff_msmpeg4_decode_block ( s , block , n , 1 , scantable ) < 0 ) return - 1 ;
 }
 if ( sub_cbp & 2 ) {
 if ( ff_msmpeg4_decode_block ( s , w -> abt_block2 [ n ] , n , 1 , scantable ) < 0 ) return - 1 ;
 }
 s -> block_last_index [ n ] = 63 ;
 return 0 ;
 }
 else {
 return ff_msmpeg4_decode_block ( s , block , n , 1 , s -> inter_scantable . permutated ) ;
 }
 }