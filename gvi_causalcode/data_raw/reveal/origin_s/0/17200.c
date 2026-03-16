static void sethhead ( struct hhead * hhead , struct hhead * vhead , struct alltabs * at , SplineFont * sf ) {
 int i , width , rbearing , height , bbearing ;
 int ymax , ymin , xmax , xmin , off ;
 DBounds bb ;
 width = 0x80000000 ;
 rbearing = 0x7fffffff ;
 height = 0x80000000 ;
 bbearing = 0x7fffffff ;
 xmax = ymax = 0x80000000 ;
 xmin = ymin = 0x7fffffff ;
 for ( i = 0 ;
 i < at -> gi . gcnt ;
 ++ i ) if ( at -> gi . bygid [ i ] != - 1 ) {
 SplineChar * sc = sf -> glyphs [ at -> gi . bygid [ i ] ] ;
 SplineCharLayerFindBounds ( sc , at -> gi . layer , & bb ) ;
 if ( sc -> width > width ) width = sc -> width ;
 if ( sc -> vwidth > height ) height = sc -> vwidth ;
 if ( sc -> width - bb . maxx < rbearing ) rbearing = sc -> width - bb . maxx ;
 if ( sc -> vwidth - bb . maxy < bbearing ) bbearing = sc -> vwidth - bb . maxy ;
 if ( bb . maxy > ymax ) ymax = bb . maxy ;
 if ( bb . miny < ymin ) ymin = bb . miny ;
 if ( bb . maxx > xmax ) xmax = bb . maxx ;
 if ( bb . minx < xmin ) xmin = bb . minx ;
 }
 if ( at -> head . ymax > ymax ) ymax = at -> head . ymax ;
 if ( at -> head . ymin < ymin ) ymin = at -> head . ymin ;
 if ( ymax == 0 && ymin == 0 ) {
 ymax = sf -> ascent ;
 ymin = - sf -> descent ;
 }
 hhead -> version = 0x00010000 ;
 if ( sf -> pfminfo . hheadascent_add ) hhead -> ascender = ymax + sf -> pfminfo . hhead_ascent ;
 else hhead -> ascender = sf -> pfminfo . hhead_ascent ;
 if ( sf -> pfminfo . hheaddescent_add ) hhead -> descender = ymin + sf -> pfminfo . hhead_descent ;
 else hhead -> descender = sf -> pfminfo . hhead_descent ;
 hhead -> linegap = sf -> pfminfo . linegap ;
 vhead -> version = 0x00011000 ;
 off = ( sf -> ascent + sf -> descent ) / 2 ;
 vhead -> ascender = xmax - off ;
 vhead -> descender = xmin - off ;
 vhead -> linegap = sf -> pfminfo . linegap ;
 at -> isfixed = at -> gi . fixed_width > 0 ;
 hhead -> maxwidth = width ;
 hhead -> minlsb = at -> head . xmin ;
 hhead -> minrsb = rbearing ;
 if ( hhead -> minlsb > 0 ) hhead -> minlsb = 0 ;
 if ( hhead -> minrsb > 0 ) hhead -> minrsb = 0 ;
 hhead -> maxextent = at -> head . xmax ;
 if ( sf -> italicangle == 0 ) hhead -> caretSlopeRise = 1 ;
 else {
 hhead -> caretSlopeRise = 100 ;
 hhead -> caretSlopeRun = ( int ) rint ( 100 * tan ( - sf -> italicangle * 3.1415926535897 / 180. ) ) ;
 }
 vhead -> maxwidth = height ;
 vhead -> minlsb = at -> head . ymin ;
 vhead -> minrsb = bbearing ;
 vhead -> maxextent = at -> head . ymax ;
 vhead -> caretSlopeRise = 0 ;
 vhead -> caretSlopeRun = 1 ;
 hhead -> numMetrics = at -> gi . hfullcnt ;
 vhead -> numMetrics = at -> gi . vfullcnt ;
 }