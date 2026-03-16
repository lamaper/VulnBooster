static void finishupcid ( SplineFont * sf , struct alltabs * at ) {
 int strlen , shlen , glen , csetlen , cstrlen , fdsellen , fdarrlen , prvlen ;
 int base , eotop , strhead ;
 int i ;
 storesid ( at , NULL ) ;
 strlen = ftell ( at -> sidf ) + ( shlen = ftell ( at -> sidh ) ) ;
 glen = ftell ( at -> globalsubrs ) ;
 csetlen = ftell ( at -> charset ) ;
 fdsellen = ftell ( at -> fdselect ) ;
 cstrlen = ftell ( at -> charstrings ) ;
 fdarrlen = ftell ( at -> fdarray ) ;
 base = ftell ( at -> cfff ) ;
 at -> cfflongoffset = true ;
 base += 5 * 4 + 4 + 2 ;
 strhead = 2 + ( at -> sidcnt > 1 ) ;
 base += strhead ;
 prvlen = 0 ;
 for ( i = 0 ;
 i < sf -> subfontcnt ;
 ++ i ) {
 fseek ( at -> fdarray , at -> fds [ i ] . fillindictmark , SEEK_SET ) ;
 dumpsizedint ( at -> fdarray , false , at -> fds [ i ] . privatelen , - 1 ) ;
 dumpsizedint ( at -> fdarray , true , base + strlen + glen + csetlen + fdsellen + cstrlen + fdarrlen + prvlen , 18 ) ;
 prvlen += ftell ( at -> fds [ i ] . private ) ;
 }
 dumpsizedint ( at -> cfff , at -> cfflongoffset , base + strlen + glen , 15 ) ;
 dumpsizedint ( at -> cfff , at -> cfflongoffset , base + strlen + glen + csetlen , ( 12 << 8 ) | 37 ) ;
 dumpsizedint ( at -> cfff , at -> cfflongoffset , base + strlen + glen + csetlen + fdsellen , 17 ) ;
 dumpsizedint ( at -> cfff , at -> cfflongoffset , base + strlen + glen + csetlen + fdsellen + cstrlen , ( 12 << 8 ) | 36 ) ;
 eotop = base - strhead - at -> lenpos - 1 ;
 fseek ( at -> cfff , at -> lenpos , SEEK_SET ) ;
 putshort ( at -> cfff , eotop ) ;
 fseek ( at -> cfff , 0 , SEEK_END ) ;
 putshort ( at -> cfff , at -> sidcnt - 1 ) ;
 if ( at -> sidcnt != 1 ) {
 putc ( at -> sidlongoffset ? 4 : 2 , at -> cfff ) ;
 if ( ! ttfcopyfile ( at -> cfff , at -> sidh , base , "CFF-StringBase" ) ) at -> error = true ;
 if ( ! ttfcopyfile ( at -> cfff , at -> sidf , base + shlen , "CFF-StringData" ) ) at -> error = true ;
 }
 if ( ! ttfcopyfile ( at -> cfff , at -> globalsubrs , base + strlen , "CFF-GlobalSubrs" ) ) at -> error = true ;
 if ( ! ttfcopyfile ( at -> cfff , at -> charset , base + strlen + glen , "CFF-Charset" ) ) at -> error = true ;
 if ( ! ttfcopyfile ( at -> cfff , at -> fdselect , base + strlen + glen + csetlen , "CFF-FDSelect" ) ) at -> error = true ;
 if ( ! ttfcopyfile ( at -> cfff , at -> charstrings , base + strlen + glen + csetlen + fdsellen , "CFF-CharStrings" ) ) at -> error = true ;
 if ( ! ttfcopyfile ( at -> cfff , at -> fdarray , base + strlen + glen + csetlen + fdsellen + cstrlen , "CFF-FDArray" ) ) at -> error = true ;
 prvlen = 0 ;
 for ( i = 0 ;
 i < sf -> subfontcnt ;
 ++ i ) {
 int temp = ftell ( at -> fds [ i ] . private ) ;
 if ( ! ttfcopyfile ( at -> cfff , at -> fds [ i ] . private , base + strlen + glen + csetlen + fdsellen + cstrlen + fdarrlen + prvlen , "CFF-PrivateSubrs" ) ) at -> error = true ;
 prvlen += temp ;
 }
 free ( at -> fds ) ;
 }