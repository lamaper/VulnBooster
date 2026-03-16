static void DumpGlyphToNameMap ( char * fontname , SplineFont * sf ) {
 char * d , * e ;
 char * newname = malloc ( strlen ( fontname ) + 10 ) ;
 FILE * file ;
 int i , k , max ;
 SplineChar * sc ;
 strcpy ( newname , fontname ) ;
 d = strrchr ( newname , '/' ) ;
 if ( d == NULL ) d = newname ;
 e = strrchr ( d , '.' ) ;
 if ( e == NULL ) e = newname + strlen ( newname ) ;
 strcpy ( e , ".g2n" ) ;
 file = fopen ( newname , "wb" ) ;
 if ( file == NULL ) {
 LogError ( _ ( "Failed to open glyph to name map file for writing: %s\n" ) , newname ) ;
 free ( newname ) ;
 return ;
 }
 if ( sf -> subfontcnt == 0 ) max = sf -> glyphcnt ;
 else {
 for ( k = max = 0 ;
 k < sf -> subfontcnt ;
 ++ k ) if ( sf -> subfonts [ k ] -> glyphcnt > max ) max = sf -> subfonts [ k ] -> glyphcnt ;
 }
 for ( i = 0 ;
 i < max ;
 ++ i ) {
 sc = NULL ;
 if ( sf -> subfontcnt == 0 ) sc = sf -> glyphs [ i ] ;
 else {
 for ( k = 0 ;
 k < sf -> subfontcnt ;
 ++ k ) if ( i < sf -> subfonts [ k ] -> glyphcnt ) if ( ( sc = sf -> subfonts [ k ] -> glyphs [ i ] ) != NULL ) break ;
 }
 if ( sc != NULL && sc -> ttf_glyph != - 1 ) {
 fprintf ( file , "GLYPHID %d\tPSNAME %s" , sc -> ttf_glyph , sc -> name ) ;
 if ( sc -> unicodeenc != - 1 ) fprintf ( file , "\tUNICODE %04X" , sc -> unicodeenc ) ;
 putc ( '\n' , file ) ;
 }
 }
 fclose ( file ) ;
 free ( newname ) ;
 }