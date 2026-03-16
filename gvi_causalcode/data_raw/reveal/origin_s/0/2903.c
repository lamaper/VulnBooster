static void FigureFullMetricsEnd ( SplineFont * sf , struct glyphinfo * gi , int istt ) {
 int i , lasti , lastv , lastdefault = istt ? 3 : 1 ;
 int width , vwidth ;
 lasti = lastv = gi -> gcnt - 1 ;
 for ( i = gi -> gcnt - 1 ;
 i > lastdefault && gi -> bygid [ i ] == - 1 ;
 -- i ) ;
 if ( i >= lastdefault ) {
 width = sf -> glyphs [ gi -> bygid [ i ] ] -> width ;
 vwidth = sf -> glyphs [ gi -> bygid [ i ] ] -> vwidth ;
 lasti = lastv = i ;
 for ( i = lasti - 1 ;
 i >= lastdefault ;
 -- i ) {
 if ( SCWorthOutputting ( sf -> glyphs [ gi -> bygid [ i ] ] ) ) {
 if ( sf -> glyphs [ gi -> bygid [ i ] ] -> width != width ) break ;
 else lasti = i ;
 }
 }
 gi -> lasthwidth = lasti ;
 if ( sf -> hasvmetrics ) {
 for ( i = lastv - 1 ;
 i >= lastdefault ;
 -- i ) {
 if ( SCWorthOutputting ( sf -> glyphs [ gi -> bygid [ i ] ] ) ) {
 if ( sf -> glyphs [ gi -> bygid [ i ] ] -> vwidth != vwidth ) break ;
 else lastv = i ;
 }
 }
 gi -> lastvwidth = lastv ;
 }
 }
 else {
 gi -> lasthwidth = 0 ;
 gi -> lastvwidth = 0 ;
 }
 }