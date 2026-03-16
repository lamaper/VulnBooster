int SSAddPoints ( SplineSet * ss , int ptcnt , BasePoint * bp , char * flags ) {
 SplinePoint * sp , * first , * nextsp ;
 int startcnt = ptcnt ;
 if ( ss -> first -> prev != NULL && ss -> first -> prev -> from -> nextcpindex == startcnt ) {
 if ( flags != NULL ) flags [ ptcnt ] = 0 ;
 bp [ ptcnt ] . x = rint ( ss -> first -> prevcp . x ) ;
 bp [ ptcnt ++ ] . y = rint ( ss -> first -> prevcp . y ) ;
 }
 else if ( ss -> first -> ttfindex != ptcnt && ss -> first -> ttfindex != 0xfffe ) IError ( "Unexpected point count in SSAddPoints" ) ;
 first = NULL ;
 for ( sp = ss -> first ;
 sp != first ;
 ) {
 if ( sp -> ttfindex != 0xffff ) {
 if ( flags != NULL ) flags [ ptcnt ] = _On_Curve ;
 bp [ ptcnt ] . x = rint ( sp -> me . x ) ;
 bp [ ptcnt ] . y = rint ( sp -> me . y ) ;
 sp -> ttfindex = ptcnt ++ ;
 }
 else if ( ! SPInterpolate ( sp ) ) {
 if ( flags != NULL ) flags [ ptcnt ] = _On_Curve ;
 bp [ ptcnt ] . x = rint ( sp -> me . x ) ;
 bp [ ptcnt ] . y = rint ( sp -> me . y ) ;
 sp -> ttfindex = ptcnt ++ ;
 }
 nextsp = sp -> next != NULL ? sp -> next -> to : NULL ;
 if ( sp -> nextcpindex == startcnt ) break ;
 if ( ( sp -> nextcpindex != 0xffff && sp -> nextcpindex != 0xfffe ) || ! sp -> nonextcp ) {
 if ( flags != NULL ) flags [ ptcnt ] = 0 ;
 bp [ ptcnt ] . x = rint ( sp -> nextcp . x ) ;
 bp [ ptcnt ++ ] . y = rint ( sp -> nextcp . y ) ;
 }
 if ( nextsp == NULL ) break ;
 if ( first == NULL ) first = sp ;
 sp = nextsp ;
 }
 return ( ptcnt ) ;
 }