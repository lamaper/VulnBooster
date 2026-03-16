static inline int ir2_get_code ( GetBitContext * gb ) {
 return get_vlc2 ( gb , ir2_vlc . table , CODE_VLC_BITS , 1 ) + 1 ;
 }