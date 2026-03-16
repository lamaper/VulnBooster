static void dumpcffcidhmtx ( struct alltabs * at , SplineFont * _sf ) {
 DBounds b ;
 SplineChar * sc ;
 int cid , i , cnt = 0 , max ;
 SplineFont * sf ;
 int dovmetrics = _sf -> hasvmetrics ;
 at -> gi . hmtx = tmpfile ( ) ;
 if ( dovmetrics ) at -> gi . vmtx = tmpfile ( ) ;
 FigureFullMetricsEnd ( _sf , & at -> gi , false ) ;
 max = 0 ;
 for ( i = 0 ;
 i < _sf -> subfontcnt ;
 ++ i ) if ( max < _sf -> subfonts [ i ] -> glyphcnt ) max = _sf -> subfonts [ i ] -> glyphcnt ;
 for ( cid = 0 ;
 cid < max ;
 ++ cid ) {
 for ( i = 0 ;
 i < _sf -> subfontcnt ;
 ++ i ) {
 sf = _sf -> subfonts [ i ] ;
 if ( cid < sf -> glyphcnt && SCWorthOutputting ( sf -> glyphs [ cid ] ) ) break ;
 }
 if ( i != _sf -> subfontcnt ) {
 sc = sf -> glyphs [ cid ] ;
 if ( sc -> ttf_glyph <= at -> gi . lasthwidth ) putshort ( at -> gi . hmtx , sc -> width ) ;
 SplineCharLayerFindBounds ( sc , at -> gi . layer , & b ) ;
 putshort ( at -> gi . hmtx , b . minx ) ;
 if ( dovmetrics ) {
 if ( sc -> ttf_glyph <= at -> gi . lastvwidth ) putshort ( at -> gi . vmtx , sc -> vwidth ) ;
 putshort ( at -> gi . vmtx , b . maxy ) ;
 }
 ++ cnt ;
 if ( sc -> ttf_glyph == at -> gi . lasthwidth ) at -> gi . hfullcnt = cnt ;
 if ( sc -> ttf_glyph == at -> gi . lastvwidth ) at -> gi . vfullcnt = cnt ;
 }
 else if ( cid == 0 ) {
 sf = _sf -> subfonts [ 0 ] ;
 putshort ( at -> gi . hmtx , sf -> ascent + sf -> descent ) ;
 putshort ( at -> gi . hmtx , 0 ) ;
 ++ cnt ;
 if ( dovmetrics ) {
 putshort ( at -> gi . vmtx , sf -> ascent + sf -> descent ) ;
 putshort ( at -> gi . vmtx , 0 ) ;
 }
 }
 }
 at -> gi . hmtxlen = ftell ( at -> gi . hmtx ) ;
 if ( at -> gi . hmtxlen & 2 ) putshort ( at -> gi . hmtx , 0 ) ;
 if ( dovmetrics ) {
 at -> gi . vmtxlen = ftell ( at -> gi . vmtx ) ;
 if ( at -> gi . vmtxlen & 2 ) putshort ( at -> gi . vmtx , 0 ) ;
 }
 at -> gi . maxp -> numGlyphs = cnt ;
 }