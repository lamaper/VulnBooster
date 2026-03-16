static inline int x8_get_orient_vlc ( IntraX8Context * w ) {
 MpegEncContext * const s = w -> s ;
 int table_index ;
 if ( ! w -> j_orient_vlc ) {
 table_index = get_bits ( & s -> gb , 1 + ( w -> quant < 13 ) ) ;
 w -> j_orient_vlc = & j_orient_vlc [ w -> quant < 13 ] [ table_index ] ;
 }
 assert ( w -> j_orient_vlc ) ;
 assert ( w -> j_orient_vlc -> table ) ;
 return get_vlc2 ( & s -> gb , w -> j_orient_vlc -> table , OR_VLC_BITS , OR_VLC_MTD ) ;
 }