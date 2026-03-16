static inline int tm2_get_token ( GetBitContext * gb , TM2Codes * code ) {
 int val ;
 val = get_vlc2 ( gb , code -> vlc . table , code -> bits , 1 ) ;
 return code -> recode [ val ] ;
 }