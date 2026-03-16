static int msmpeg4v2_decode_motion ( MpegEncContext * s , int pred , int f_code ) {
 int code , val , sign , shift ;
 code = get_vlc2 ( & s -> gb , v2_mv_vlc . table , V2_MV_VLC_BITS , 2 ) ;
 av_dlog ( s , "MV code %d at %d %d pred: %d\n" , code , s -> mb_x , s -> mb_y , pred ) ;
 if ( code < 0 ) return 0xffff ;
 if ( code == 0 ) return pred ;
 sign = get_bits1 ( & s -> gb ) ;
 shift = f_code - 1 ;
 val = code ;
 if ( shift ) {
 val = ( val - 1 ) << shift ;
 val |= get_bits ( & s -> gb , shift ) ;
 val ++ ;
 }
 if ( sign ) val = - val ;
 val += pred ;
 if ( val <= - 64 ) val += 64 ;
 else if ( val >= 64 ) val -= 64 ;
 return val ;
 }