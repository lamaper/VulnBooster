static void circlearcto ( real a1 , real a2 , real cx , real cy , real r , SplineSet * cur , real * transform ) {
 SplinePoint * pt ;
 DBasePoint temp , base , cp ;
 real cplen ;
 int sign = 1 ;
 real s1 , s2 , c1 , c2 ;
 if ( a1 == a2 ) return ;
 cplen = ( a2 - a1 ) / 90 * r * .552 ;
 a1 *= 3.1415926535897932 / 180 ;
 a2 *= 3.1415926535897932 / 180 ;
 s1 = sin ( a1 ) ;
 s2 = sin ( a2 ) ;
 c1 = cos ( a1 ) ;
 c2 = cos ( a2 ) ;
 temp . x = cx + r * c2 ;
 temp . y = cy + r * s2 ;
 base . x = cx + r * c1 ;
 base . y = cy + r * s1 ;
 pt = chunkalloc ( sizeof ( SplinePoint ) ) ;
 Transform ( & pt -> me , & temp , transform ) ;
 cp . x = temp . x - cplen * s2 ;
 cp . y = temp . y + cplen * c2 ;
 if ( ( cp . x - base . x ) * ( cp . x - base . x ) + ( cp . y - base . y ) * ( cp . y - base . y ) > ( temp . x - base . x ) * ( temp . x - base . x ) + ( temp . y - base . y ) * ( temp . y - base . y ) ) {
 sign = - 1 ;
 cp . x = temp . x + cplen * s2 ;
 cp . y = temp . y - cplen * c2 ;
 }
 Transform ( & pt -> prevcp , & cp , transform ) ;
 pt -> nonextcp = true ;
 cp . x = base . x + sign * cplen * s1 ;
 cp . y = base . y - sign * cplen * c1 ;
 Transform ( & cur -> last -> nextcp , & cp , transform ) ;
 cur -> last -> nonextcp = false ;
 CheckMake ( cur -> last , pt ) ;
 SplineMake3 ( cur -> last , pt ) ;
 cur -> last = pt ;
 }