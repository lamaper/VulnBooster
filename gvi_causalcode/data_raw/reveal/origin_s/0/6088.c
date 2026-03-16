static int mp_gradient ( MotionPixelsContext * mp , int component , int v ) {
 int delta ;
 delta = ( v - 7 ) * mp -> gradient_scale [ component ] ;
 mp -> gradient_scale [ component ] = ( v == 0 || v == 14 ) ? 2 : 1 ;
 return delta ;
 }