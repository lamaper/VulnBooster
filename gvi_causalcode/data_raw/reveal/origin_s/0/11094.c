static int dumpcffhmtx ( struct alltabs * at , SplineFont * sf , int bitmaps ) {
 DBounds b ;
 SplineChar * sc ;
 int i , cnt ;
 int dovmetrics = sf -> hasvmetrics ;
 int width = at -> gi . fixed_width ;
 at -> gi . hmtx = tmpfile ( ) ;
 if ( dovmetrics ) at -> gi . vmtx = tmpfile ( ) ;
 FigureFullMetricsEnd ( sf , & at -> gi , bitmaps ) ;
 if ( at -> gi . bygid [ 0 ] != - 1 && ( sf -> glyphs [ at -> gi . bygid [ 0 ] ] -> width == width || width <= 0 ) ) {
 putshort ( at -> gi . hmtx , sf -> glyphs [ at -> gi . bygid [ 0 ] ] -> width ) ;
 SplineCharLayerFindBounds ( sf -> glyphs [ at -> gi . bygid [ 0 ] ] , at -> gi . layer , & b ) ;
 putshort ( at -> gi . hmtx , b . minx ) ;
 if ( dovmetrics ) {
 putshort ( at -> gi . vmtx , sf -> glyphs [ at -> gi . bygid [ 0 ] ] -> vwidth ) ;
 putshort ( at -> gi . vmtx , b . miny ) ;
 }
 }
 else {
 putshort ( at -> gi . hmtx , width <= 0 ? ( sf -> ascent + sf -> descent ) / 2 : width ) ;
 putshort ( at -> gi . hmtx , 0 ) ;
 if ( dovmetrics ) {
 putshort ( at -> gi . vmtx , sf -> ascent + sf -> descent ) ;
 putshort ( at -> gi . vmtx , 0 ) ;
 }
 }
 cnt = 1 ;
 if ( bitmaps ) {
 if ( width <= 0 ) width = ( sf -> ascent + sf -> descent ) / 3 ;
 putshort ( at -> gi . hmtx , width ) ;
 putshort ( at -> gi . hmtx , 0 ) ;
 if ( dovmetrics ) {
 putshort ( at -> gi . vmtx , sf -> ascent + sf -> descent ) ;
 putshort ( at -> gi . vmtx , 0 ) ;
 }
 putshort ( at -> gi . hmtx , width ) ;
 putshort ( at -> gi . hmtx , 0 ) ;
 if ( dovmetrics ) {
 putshort ( at -> gi . vmtx , sf -> ascent + sf -> descent ) ;
 putshort ( at -> gi . vmtx , 0 ) ;
 }
 cnt = 3 ;
 }
 for ( i = cnt ;
 i < at -> gi . gcnt ;
 ++ i ) if ( at -> gi . bygid [ i ] != - 1 ) {
 sc = sf -> glyphs [ at -> gi . bygid [ i ] ] ;
 if ( SCWorthOutputting ( sc ) ) {
 if ( i <= at -> gi . lasthwidth ) putshort ( at -> gi . hmtx , sc -> width ) ;
 SplineCharLayerFindBounds ( sc , at -> gi . layer , & b ) ;
 putshort ( at -> gi . hmtx , b . minx ) ;
 if ( dovmetrics ) {
 if ( i <= at -> gi . lastvwidth ) putshort ( at -> gi . vmtx , sc -> vwidth ) ;
 putshort ( at -> gi . vmtx , b . maxy ) ;
 }
 ++ cnt ;
 if ( i == at -> gi . lasthwidth ) at -> gi . hfullcnt = cnt ;
 if ( i == at -> gi . lastvwidth ) at -> gi . vfullcnt = cnt ;
 }
 }
 at -> gi . hmtxlen = ftell ( at -> gi . hmtx ) ;
 if ( at -> gi . hmtxlen & 2 ) putshort ( at -> gi . hmtx , 0 ) ;
 if ( dovmetrics ) {
 at -> gi . vmtxlen = ftell ( at -> gi . vmtx ) ;
 if ( at -> gi . vmtxlen & 2 ) putshort ( at -> gi . vmtx , 0 ) ;
 }
 at -> gi . maxp -> numGlyphs = cnt ;
 return ( true ) ;
 }