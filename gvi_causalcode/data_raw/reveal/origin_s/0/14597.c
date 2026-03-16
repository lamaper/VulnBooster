static void AbortTTF ( struct alltabs * at , SplineFont * sf ) {
 int i ;
 if ( at -> loca != NULL ) fclose ( at -> loca ) ;
 if ( at -> name != NULL ) fclose ( at -> name ) ;
 if ( at -> post != NULL ) fclose ( at -> post ) ;
 if ( at -> gpos != NULL ) fclose ( at -> gpos ) ;
 if ( at -> gsub != NULL ) fclose ( at -> gsub ) ;
 if ( at -> gdef != NULL ) fclose ( at -> gdef ) ;
 if ( at -> kern != NULL ) fclose ( at -> kern ) ;
 if ( at -> cmap != NULL ) fclose ( at -> cmap ) ;
 if ( at -> headf != NULL ) fclose ( at -> headf ) ;
 if ( at -> hheadf != NULL ) fclose ( at -> hheadf ) ;
 if ( at -> maxpf != NULL ) fclose ( at -> maxpf ) ;
 if ( at -> os2f != NULL ) fclose ( at -> os2f ) ;
 if ( at -> cvtf != NULL ) fclose ( at -> cvtf ) ;
 if ( at -> vheadf != NULL ) fclose ( at -> vheadf ) ;
 if ( at -> vorgf != NULL ) fclose ( at -> vorgf ) ;
 if ( at -> cfff != NULL ) fclose ( at -> cfff ) ;
 if ( at -> gi . glyphs != NULL ) fclose ( at -> gi . glyphs ) ;
 if ( at -> gi . hmtx != NULL ) fclose ( at -> gi . hmtx ) ;
 if ( at -> gi . vmtx != NULL ) fclose ( at -> gi . vmtx ) ;
 if ( at -> fpgmf != NULL ) fclose ( at -> fpgmf ) ;
 if ( at -> prepf != NULL ) fclose ( at -> prepf ) ;
 if ( at -> gaspf != NULL ) fclose ( at -> gaspf ) ;
 if ( at -> sidf != NULL ) fclose ( at -> sidf ) ;
 if ( at -> sidh != NULL ) fclose ( at -> sidh ) ;
 if ( at -> charset != NULL ) fclose ( at -> charset ) ;
 if ( at -> encoding != NULL ) fclose ( at -> encoding ) ;
 if ( at -> private != NULL ) fclose ( at -> private ) ;
 if ( at -> charstrings != NULL ) fclose ( at -> charstrings ) ;
 if ( at -> fdselect != NULL ) fclose ( at -> fdselect ) ;
 if ( at -> fdarray != NULL ) fclose ( at -> fdarray ) ;
 if ( at -> bdat != NULL ) fclose ( at -> bdat ) ;
 if ( at -> bloc != NULL ) fclose ( at -> bloc ) ;
 if ( at -> ebsc != NULL ) fclose ( at -> ebsc ) ;
 if ( at -> prop != NULL ) fclose ( at -> prop ) ;
 if ( at -> opbd != NULL ) fclose ( at -> opbd ) ;
 if ( at -> acnt != NULL ) fclose ( at -> acnt ) ;
 if ( at -> lcar != NULL ) fclose ( at -> lcar ) ;
 if ( at -> feat != NULL ) fclose ( at -> feat ) ;
 if ( at -> morx != NULL ) fclose ( at -> morx ) ;
 if ( at -> pfed != NULL ) fclose ( at -> pfed ) ;
 if ( at -> tex != NULL ) fclose ( at -> tex ) ;
 if ( at -> gvar != NULL ) fclose ( at -> gvar ) ;
 if ( at -> fvar != NULL ) fclose ( at -> fvar ) ;
 if ( at -> cvar != NULL ) fclose ( at -> cvar ) ;
 if ( at -> avar != NULL ) fclose ( at -> avar ) ;
 for ( i = 0 ;
 i < sf -> subfontcnt ;
 ++ i ) {
 if ( at -> fds [ i ] . private != NULL ) fclose ( at -> fds [ i ] . private ) ;
 }
 if ( sf -> subfontcnt != 0 ) {
 free ( sf -> glyphs ) ;
 sf -> glyphs = NULL ;
 sf -> glyphcnt = sf -> glyphmax = 0 ;
 }
 free ( at -> fds ) ;
 free ( at -> gi . bygid ) ;
 }