static int dumpcidglyphs ( SplineFont * sf , struct alltabs * at ) {
 int i ;
 struct pschars * glbls = NULL , * chrs ;
 at -> cfff = tmpfile ( ) ;
 at -> sidf = tmpfile ( ) ;
 at -> sidh = tmpfile ( ) ;
 at -> charset = tmpfile ( ) ;
 at -> fdselect = tmpfile ( ) ;
 at -> fdarray = tmpfile ( ) ;
 at -> globalsubrs = tmpfile ( ) ;
 at -> fds = calloc ( sf -> subfontcnt , sizeof ( struct fd2data ) ) ;
 for ( i = 0 ;
 i < sf -> subfontcnt ;
 ++ i ) {
 at -> fds [ i ] . private = tmpfile ( ) ;
 ATFigureDefWidth ( sf -> subfonts [ i ] , at , i ) ;
 }
 if ( ( chrs = CID2ChrsSubrs2 ( sf , at -> fds , at -> gi . flags , & glbls , at -> gi . layer ) ) == NULL ) return ( false ) ;
 for ( i = 0 ;
 i < sf -> subfontcnt ;
 ++ i ) {
 dumpcffprivate ( sf -> subfonts [ i ] , at , i , at -> fds [ i ] . subrs -> next ) ;
 if ( at -> fds [ i ] . subrs -> next != 0 ) _dumpcffstrings ( at -> fds [ i ] . private , at -> fds [ i ] . subrs ) ;
 PSCharsFree ( at -> fds [ i ] . subrs ) ;
 }
 _dumpcffstrings ( at -> globalsubrs , glbls ) ;
 PSCharsFree ( glbls ) ;
 dumpcffheader ( at -> cfff ) ;
 dumpcffnames ( sf , at -> cfff ) ;
 dumpcffcidset ( at ) ;
 dumpcfffdselect ( sf , at ) ;
 dumpcffdictindex ( sf , at ) ;
 if ( ( at -> charstrings = dumpcffstrings ( chrs ) ) == NULL ) return ( false ) ;
 dumpcffcidtopdict ( sf , at ) ;
 finishupcid ( sf , at ) ;
 at -> cfflen = ftell ( at -> cfff ) ;
 if ( at -> cfflen & 3 ) {
 for ( i = 4 - ( at -> cfflen & 3 ) ;
 i > 0 ;
 -- i ) putc ( '\0' , at -> cfff ) ;
 }
 if ( at -> format != ff_cffcid ) dumpcffcidhmtx ( at , sf ) ;
 return ( true ) ;
 }