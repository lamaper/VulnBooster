static int set_palette ( BethsoftvidContext * ctx ) {
 uint32_t * palette = ( uint32_t * ) ctx -> frame . data [ 1 ] ;
 int a ;
 if ( bytestream2_get_bytes_left ( & ctx -> g ) < 256 * 3 ) return AVERROR_INVALIDDATA ;
 for ( a = 0 ;
 a < 256 ;
 a ++ ) {
 palette [ a ] = bytestream2_get_be24u ( & ctx -> g ) * 4 ;
 }
 ctx -> frame . palette_has_changed = 1 ;
 return 0 ;
 }