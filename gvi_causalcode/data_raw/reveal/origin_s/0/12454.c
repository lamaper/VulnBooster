static void dumpcffprivate ( SplineFont * sf , struct alltabs * at , int subfont , int subrcnt ) {
 char * pt ;
 FILE * private = subfont == - 1 ? at -> private : at -> fds [ subfont ] . private ;
 int mi , i ;
 real bluevalues [ 14 ] , otherblues [ 10 ] ;
 real snapcnt [ 12 ] ;
 real stemsnaph [ 12 ] , stemsnapv [ 12 ] ;
 real stdhw [ 1 ] , stdvw [ 1 ] ;
 int hasblue = 0 , hash = 0 , hasv = 0 , bs ;
 int nomwid , defwid ;
 EncMap * map = at -> map ;
 double bluescale ;
 if ( subfont == - 1 ) defwid = at -> defwid ;
 else defwid = at -> fds [ subfont ] . defwid ;
 dumpintoper ( private , defwid , 20 ) ;
 if ( subfont == - 1 ) nomwid = at -> nomwid ;
 else nomwid = at -> fds [ subfont ] . nomwid ;
 dumpintoper ( private , nomwid , 21 ) ;
 bs = SplineFontIsFlexible ( sf , at -> gi . layer , at -> gi . flags ) ;
 hasblue = PSDictHasEntry ( sf -> private , "BlueValues" ) != NULL ;
 hash = PSDictHasEntry ( sf -> private , "StdHW" ) != NULL ;
 hasv = PSDictHasEntry ( sf -> private , "StdVW" ) != NULL ;
 ff_progress_change_stages ( 2 + autohint_before_generate + ! hasblue ) ;
 if ( autohint_before_generate ) {
 ff_progress_change_line1 ( _ ( "Auto Hinting Font..." ) ) ;
 SplineFontAutoHint ( sf , at -> gi . layer ) ;
 ff_progress_next_stage ( ) ;
 }
 otherblues [ 0 ] = otherblues [ 1 ] = bluevalues [ 0 ] = bluevalues [ 1 ] = 0 ;
 if ( ! hasblue ) {
 FindBlues ( sf , at -> gi . layer , bluevalues , otherblues ) ;
 ff_progress_next_stage ( ) ;
 }
 stdhw [ 0 ] = stdvw [ 0 ] = 0 ;
 if ( ! hash ) {
 FindHStems ( sf , stemsnaph , snapcnt ) ;
 mi = - 1 ;
 for ( i = 0 ;
 i < 12 && stemsnaph [ i ] != 0 ;
 ++ i ) if ( mi == - 1 ) mi = i ;
 else if ( snapcnt [ i ] > snapcnt [ mi ] ) mi = i ;
 if ( mi != - 1 ) stdhw [ 0 ] = stemsnaph [ mi ] ;
 }
 if ( ! hasv ) {
 FindVStems ( sf , stemsnapv , snapcnt ) ;
 mi = - 1 ;
 for ( i = 0 ;
 i < 12 && stemsnapv [ i ] != 0 ;
 ++ i ) if ( mi == - 1 ) mi = i ;
 else if ( snapcnt [ i ] > snapcnt [ mi ] ) mi = i ;
 if ( mi != - 1 ) stdvw [ 0 ] = stemsnapv [ mi ] ;
 }
 ff_progress_change_line1 ( _ ( "Saving OpenType Font" ) ) ;
 if ( hasblue ) DumpStrArray ( PSDictHasEntry ( sf -> private , "BlueValues" ) , private , 6 ) ;
 else DumpDblArray ( bluevalues , sizeof ( bluevalues ) / sizeof ( bluevalues [ 0 ] ) , private , 6 ) ;
 if ( ( pt = PSDictHasEntry ( sf -> private , "OtherBlues" ) ) != NULL ) DumpStrArray ( pt , private , 7 ) ;
 else if ( ! hasblue ) DumpDblArray ( otherblues , sizeof ( otherblues ) / sizeof ( otherblues [ 0 ] ) , private , 7 ) ;
 if ( ( pt = PSDictHasEntry ( sf -> private , "FamilyBlues" ) ) != NULL ) DumpStrArray ( pt , private , 8 ) ;
 bluescale = BlueScaleFigure ( sf -> private , bluevalues , otherblues ) ;
 if ( ( pt = PSDictHasEntry ( sf -> private , "FamilyOtherBlues" ) ) != NULL ) DumpStrArray ( pt , private , 9 ) ;
 if ( ( pt = PSDictHasEntry ( sf -> private , "BlueScale" ) ) != NULL ) DumpStrDouble ( pt , private , ( 12 << 8 ) + 9 ) ;
 else if ( bluescale != - 1 ) dumpdbloper ( private , bluescale , ( 12 << 8 ) + 9 ) ;
 if ( ( pt = PSDictHasEntry ( sf -> private , "BlueShift" ) ) != NULL ) DumpStrDouble ( pt , private , ( 12 << 8 ) + 10 ) ;
 else dumpintoper ( private , bs , ( 12 << 8 ) + 10 ) ;
 if ( ( pt = PSDictHasEntry ( sf -> private , "BlueFuzz" ) ) != NULL ) DumpStrDouble ( pt , private , ( 12 << 8 ) + 11 ) ;
 if ( hash ) {
 DumpStrDouble ( PSDictHasEntry ( sf -> private , "StdHW" ) , private , 10 ) ;
 if ( ( pt = PSDictHasEntry ( sf -> private , "StemSnapH" ) ) != NULL ) DumpStrArray ( pt , private , ( 12 << 8 ) | 12 ) ;
 }
 else {
 if ( stdhw [ 0 ] != 0 ) dumpdbloper ( private , stdhw [ 0 ] , 10 ) ;
 DumpDblArray ( stemsnaph , sizeof ( stemsnaph ) / sizeof ( stemsnaph [ 0 ] ) , private , ( 12 << 8 ) | 12 ) ;
 }
 if ( hasv ) {
 DumpStrDouble ( PSDictHasEntry ( sf -> private , "StdVW" ) , private , 11 ) ;
 if ( ( pt = PSDictHasEntry ( sf -> private , "StemSnapV" ) ) != NULL ) DumpStrArray ( pt , private , ( 12 << 8 ) | 13 ) ;
 }
 else {
 if ( stdvw [ 0 ] != 0 ) dumpdbloper ( private , stdvw [ 0 ] , 11 ) ;
 DumpDblArray ( stemsnapv , sizeof ( stemsnapv ) / sizeof ( stemsnapv [ 0 ] ) , private , ( 12 << 8 ) | 13 ) ;
 }
 if ( ( pt = PSDictHasEntry ( sf -> private , "ForceBold" ) ) != NULL ) {
 dumpintoper ( private , * pt == 't' || * pt == 'T' , ( 12 << 8 ) | 14 ) ;
 }
 else if ( sf -> weight != NULL && ( strstrmatch ( sf -> weight , "Bold" ) != NULL || strstrmatch ( sf -> weight , "Demi" ) != NULL || strstrmatch ( sf -> weight , "Fett" ) != NULL || strstrmatch ( sf -> weight , "Gras" ) != NULL || strstrmatch ( sf -> weight , "Heavy" ) != NULL || strstrmatch ( sf -> weight , "Black" ) != NULL ) ) dumpintoper ( private , 1 , ( 12 << 8 ) | 14 ) ;
 if ( ( pt = PSDictHasEntry ( sf -> private , "LanguageGroup" ) ) != NULL ) DumpStrDouble ( pt , private , ( 12 << 8 ) + 17 ) ;
 else if ( map == NULL ) ;
 else if ( map -> enc -> is_japanese || map -> enc -> is_korean || map -> enc -> is_tradchinese || map -> enc -> is_simplechinese ) dumpintoper ( private , 1 , ( 12 << 8 ) | 17 ) ;
 if ( ( pt = PSDictHasEntry ( sf -> private , "ExpansionFactor" ) ) != NULL ) DumpStrDouble ( pt , private , ( 12 << 8 ) + 18 ) ;
 if ( subrcnt != 0 ) dumpsizedint ( private , false , ftell ( private ) + 3 + 1 , 19 ) ;
 if ( subfont == - 1 ) at -> privatelen = ftell ( private ) ;
 else at -> fds [ subfont ] . privatelen = ftell ( private ) ;
 }