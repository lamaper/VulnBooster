static inline int get_coeff ( GetBitContext * gb , VLC * vlc ) {
 int val = get_vlc2 ( gb , vlc -> table , vlc -> bits , 2 ) ;
 return get_coeff_bits ( gb , val ) ;
 }