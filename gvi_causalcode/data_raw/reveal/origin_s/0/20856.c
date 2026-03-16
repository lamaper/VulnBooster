static void dumppointarrays ( struct glyphinfo * gi , BasePoint * bp , char * fs , int pc ) {
 BasePoint last ;
 int i , flags ;
 int lastflag , flagcnt ;
 if ( gi -> maxp -> maxPoints < pc ) gi -> maxp -> maxPoints = pc ;
 last . x = last . y = 0 ;
 lastflag = - 1 ;
 flagcnt = 0 ;
 for ( i = 0 ;
 i < pc ;
 ++ i ) {
 flags = 0 ;
 if ( fs == NULL || fs [ i ] ) flags = _On_Curve ;
 if ( last . x == bp [ i ] . x ) flags |= _X_Same ;
 else if ( bp [ i ] . x - last . x > - 256 && bp [ i ] . x - last . x < 255 ) {
 flags |= _X_Short ;
 if ( bp [ i ] . x >= last . x ) flags |= _X_Same ;
 }
 if ( last . y == bp [ i ] . y ) flags |= _Y_Same ;
 else if ( bp [ i ] . y - last . y > - 256 && bp [ i ] . y - last . y < 255 ) {
 flags |= _Y_Short ;
 if ( bp [ i ] . y >= last . y ) flags |= _Y_Same ;
 }
 last = bp [ i ] ;
 if ( lastflag == - 1 ) {
 lastflag = flags ;
 flagcnt = 0 ;
 }
 else if ( flags != lastflag ) {
 if ( flagcnt != 0 ) lastflag |= _Repeat ;
 putc ( lastflag , gi -> glyphs ) ;
 if ( flagcnt != 0 ) putc ( flagcnt , gi -> glyphs ) ;
 lastflag = flags ;
 flagcnt = 0 ;
 }
 else {
 if ( ++ flagcnt == 255 ) {
 putc ( lastflag | _Repeat , gi -> glyphs ) ;
 putc ( 255 , gi -> glyphs ) ;
 lastflag = - 1 ;
 flagcnt = 0 ;
 }
 }
 }
 if ( lastflag != - 1 ) {
 if ( flagcnt != 0 ) lastflag |= _Repeat ;
 putc ( lastflag , gi -> glyphs ) ;
 if ( flagcnt != 0 ) putc ( flagcnt , gi -> glyphs ) ;
 }
 last . x = 0 ;
 for ( i = 0 ;
 i < pc ;
 ++ i ) {
 if ( last . x == bp [ i ] . x ) ;
 else if ( bp [ i ] . x - last . x > - 256 && bp [ i ] . x - last . x < 255 ) {
 if ( bp [ i ] . x >= last . x ) putc ( bp [ i ] . x - last . x , gi -> glyphs ) ;
 else putc ( last . x - bp [ i ] . x , gi -> glyphs ) ;
 }
 else putshort ( gi -> glyphs , bp [ i ] . x - last . x ) ;
 last . x = bp [ i ] . x ;
 }
 last . y = 0 ;
 for ( i = 0 ;
 i < pc ;
 ++ i ) {
 if ( last . y == bp [ i ] . y ) ;
 else if ( bp [ i ] . y - last . y > - 256 && bp [ i ] . y - last . y < 255 ) {
 if ( bp [ i ] . y >= last . y ) putc ( bp [ i ] . y - last . y , gi -> glyphs ) ;
 else putc ( last . y - bp [ i ] . y , gi -> glyphs ) ;
 }
 else putshort ( gi -> glyphs , bp [ i ] . y - last . y ) ;
 last . y = bp [ i ] . y ;
 }
 if ( ftell ( gi -> glyphs ) & 1 ) putc ( '\0' , gi -> glyphs ) ;
 }