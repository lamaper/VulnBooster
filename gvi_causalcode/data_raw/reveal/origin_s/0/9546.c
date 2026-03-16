static int dumptype2glyphs ( SplineFont * sf , struct alltabs * at ) {
 int i ;
 struct pschars * subrs , * chrs ;
 at -> cfff = tmpfile ( ) ;
 at -> sidf = tmpfile ( ) ;
 at -> sidh = tmpfile ( ) ;
 at -> charset = tmpfile ( ) ;
 at -> encoding = tmpfile ( ) ;
 at -> private = tmpfile ( ) ;
 dumpcffheader ( at -> cfff ) ;
 dumpcffnames ( sf , at -> cfff ) ;
 dumpcffcharset ( sf , at ) ;
 ff_progress_change_stages ( 2 + at -> gi . strikecnt ) ;
 ATFigureDefWidth ( sf , at , - 1 ) ;
 if ( ( chrs = SplineFont2ChrsSubrs2 ( sf , at -> nomwid , at -> defwid , at -> gi . bygid , at -> gi . gcnt , at -> gi . flags , & subrs , at -> gi . layer ) ) == NULL ) return ( false ) ;
 dumpcffprivate ( sf , at , - 1 , subrs -> next ) ;
 if ( subrs -> next != 0 ) _dumpcffstrings ( at -> private , subrs ) ;
 ff_progress_next_stage ( ) ;
 at -> charstrings = dumpcffstrings ( chrs ) ;
 PSCharsFree ( subrs ) ;
 if ( at -> charstrings == NULL ) return ( false ) ;
 if ( at -> format == ff_cff && ! isStdEncoding ( sf , at -> map ) ) dumpcffencoding ( sf , at ) ;
 dumpcfftopdict ( sf , at ) ;
 finishup ( sf , at ) ;
 at -> cfflen = ftell ( at -> cfff ) ;
 if ( at -> cfflen & 3 ) {
 for ( i = 4 - ( at -> cfflen & 3 ) ;
 i > 0 ;
 -- i ) putc ( '\0' , at -> cfff ) ;
 }
 if ( at -> format != ff_cff ) dumpcffhmtx ( at , sf , false ) ;
 free ( at -> gn_sid ) ;
 at -> gn_sid = NULL ;
 return ( true ) ;
 }