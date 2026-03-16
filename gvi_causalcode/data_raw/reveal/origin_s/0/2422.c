static int AnyMisleadingBitmapAdvances ( SplineFont * sf , int32 * bsizes ) {
 int strike , gid ;
 double em = sf -> ascent + sf -> descent ;
 BDFFont * bdf ;
 if ( bsizes == NULL ) return ( false ) ;
 for ( strike = 0 ;
 bsizes [ strike ] != 0 ;
 ++ strike ) {
 for ( bdf = sf -> bitmaps ;
 bdf != NULL && ( bdf -> pixelsize != ( bsizes [ strike ] & 0xffff ) || BDFDepth ( bdf ) != ( bsizes [ strike ] >> 16 ) ) ;
 bdf = bdf -> next ) ;
 if ( bdf == NULL ) continue ;
 for ( gid = 0 ;
 gid < sf -> glyphcnt && gid < bdf -> glyphcnt ;
 ++ gid ) {
 SplineChar * sc = sf -> glyphs [ gid ] ;
 BDFChar * bc = bdf -> glyphs [ gid ] ;
 if ( sc == NULL || bc == NULL ) continue ;
 if ( ( int ) rint ( ( sc -> width * bdf -> pixelsize ) / em ) != bc -> width ) return ( true ) ;
 }
 }
 return ( false ) ;
 }