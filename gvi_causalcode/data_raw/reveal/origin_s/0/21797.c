static void use_normal_update_speed ( WmallDecodeCtx * s , int ich ) {
 int ilms , recent , icoef ;
 for ( ilms = s -> cdlms_ttl [ ich ] - 1 ;
 ilms >= 0 ;
 ilms -- ) {
 recent = s -> cdlms [ ich ] [ ilms ] . recent ;
 if ( s -> update_speed [ ich ] == 8 ) continue ;
 if ( s -> bV3RTM ) for ( icoef = 0 ;
 icoef < s -> cdlms [ ich ] [ ilms ] . order ;
 icoef ++ ) s -> cdlms [ ich ] [ ilms ] . lms_updates [ icoef + recent ] /= 2 ;
 else for ( icoef = 0 ;
 icoef < s -> cdlms [ ich ] [ ilms ] . order ;
 icoef ++ ) s -> cdlms [ ich ] [ ilms ] . lms_updates [ icoef ] /= 2 ;
 }
 s -> update_speed [ ich ] = 8 ;
 }