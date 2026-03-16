static void finishup ( SplineFont * sf , struct alltabs * at ) {
 int strlen , shlen , glen , enclen , csetlen , cstrlen , prvlen ;
 int base , eotop , strhead ;
 int output_enc = ( at -> format == ff_cff && ! isStdEncoding ( sf , at -> map ) ) ;
 storesid ( at , NULL ) ;
 strlen = ftell ( at -> sidf ) + ( shlen = ftell ( at -> sidh ) ) ;
 glen = sizeof ( short ) ;
 enclen = ftell ( at -> encoding ) ;
 csetlen = ftell ( at -> charset ) ;
 cstrlen = ftell ( at -> charstrings ) ;
 prvlen = ftell ( at -> private ) ;
 base = ftell ( at -> cfff ) ;
 if ( base + 6 * 3 + strlen + glen + enclen + csetlen + cstrlen + prvlen > 32767 ) {
 at -> cfflongoffset = true ;
 base += 5 * 5 + 4 ;
 }
 else base += 5 * 3 + 4 ;
 strhead = 2 + ( at -> sidcnt > 1 ) ;
 base += strhead ;
 dumpsizedint ( at -> cfff , at -> cfflongoffset , base + strlen + glen , 15 ) ;
 if ( output_enc ) dumpsizedint ( at -> cfff , at -> cfflongoffset , base + strlen + glen + csetlen , 16 ) ;
 else {
 dumpsizedint ( at -> cfff , at -> cfflongoffset , 0 , 16 ) ;
 enclen = 0 ;
 }
 dumpsizedint ( at -> cfff , at -> cfflongoffset , base + strlen + glen + csetlen + enclen , 17 ) ;
 dumpsizedint ( at -> cfff , at -> cfflongoffset , at -> privatelen , - 1 ) ;
 dumpsizedint ( at -> cfff , at -> cfflongoffset , base + strlen + glen + csetlen + enclen + cstrlen , 18 ) ;
 eotop = base - strhead - at -> lenpos - 1 ;
 if ( at -> cfflongoffset ) {
 fseek ( at -> cfff , 3 , SEEK_SET ) ;
 putc ( 4 , at -> cfff ) ;
 }
 fseek ( at -> cfff , at -> lenpos , SEEK_SET ) ;
 putshort ( at -> cfff , eotop ) ;
 fseek ( at -> cfff , 0 , SEEK_END ) ;
 putshort ( at -> cfff , at -> sidcnt - 1 ) ;
 if ( at -> sidcnt != 1 ) {
 putc ( at -> sidlongoffset ? 4 : 2 , at -> cfff ) ;
 if ( ! ttfcopyfile ( at -> cfff , at -> sidh , base , "CFF-StringBase" ) ) at -> error = true ;
 if ( ! ttfcopyfile ( at -> cfff , at -> sidf , base + shlen , "CFF-StringData" ) ) at -> error = true ;
 }
 putshort ( at -> cfff , 0 ) ;
 if ( ! ttfcopyfile ( at -> cfff , at -> charset , base + strlen + glen , "CFF-Charset" ) ) at -> error = true ;
 if ( ! ttfcopyfile ( at -> cfff , at -> encoding , base + strlen + glen + csetlen , "CFF-Encoding" ) ) at -> error = true ;
 if ( ! ttfcopyfile ( at -> cfff , at -> charstrings , base + strlen + glen + csetlen + enclen , "CFF-CharStrings" ) ) at -> error = true ;
 if ( ! ttfcopyfile ( at -> cfff , at -> private , base + strlen + glen + csetlen + enclen + cstrlen , "CFF-Private" ) ) at -> error = true ;
 }