static void dumpcffencoding ( SplineFont * sf , struct alltabs * at ) {
 int i , cnt , anydups ;
 uint32 start_pos = ftell ( at -> encoding ) ;
 SplineChar * sc ;
 EncMap * map = at -> map ;
 putc ( 0 , at -> encoding ) ;
 putc ( 0xff , at -> encoding ) ;
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( sf -> glyphs [ i ] != NULL ) sf -> glyphs [ i ] -> ticked = false ;
 cnt = 0 ;
 anydups = 0 ;
 for ( i = 0 ;
 i < 256 && i < map -> enccount ;
 ++ i ) if ( map -> map [ i ] != - 1 && ( sc = sf -> glyphs [ map -> map [ i ] ] ) != NULL ) {
 if ( sc -> ttf_glyph > 255 ) continue ;
 if ( sc -> ticked ) {
 ++ anydups ;
 }
 else if ( sc -> ttf_glyph > 0 ) {
 if ( cnt >= 255 ) break ;
 putc ( i , at -> encoding ) ;
 ++ cnt ;
 sc -> ticked = true ;
 }
 }
 if ( anydups ) {
 fseek ( at -> encoding , start_pos , SEEK_SET ) ;
 putc ( 0x80 , at -> encoding ) ;
 putc ( cnt , at -> encoding ) ;
 fseek ( at -> encoding , 0 , SEEK_END ) ;
 putc ( anydups , at -> encoding ) ;
 for ( i = 0 ;
 i < sf -> glyphcnt ;
 ++ i ) if ( sf -> glyphs [ i ] != NULL ) sf -> glyphs [ i ] -> ticked = false ;
 for ( i = 0 ;
 i < 256 && i < map -> enccount ;
 ++ i ) if ( map -> map [ i ] != - 1 && ( sc = sf -> glyphs [ map -> map [ i ] ] ) != NULL ) {
 if ( sc -> ttf_glyph > 255 ) continue ;
 if ( sc -> ticked ) {
 putc ( i , at -> encoding ) ;
 putshort ( at -> encoding , at -> gn_sid [ sc -> ttf_glyph ] ) ;
 }
 sc -> ticked = true ;
 }
 }
 else {
 fseek ( at -> encoding , start_pos + 1 , SEEK_SET ) ;
 putc ( cnt , at -> encoding ) ;
 fseek ( at -> encoding , 0 , SEEK_END ) ;
 }
 free ( at -> gn_sid ) ;
 at -> gn_sid = NULL ;
 }