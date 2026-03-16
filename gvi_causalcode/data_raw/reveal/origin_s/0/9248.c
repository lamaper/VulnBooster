static void dumpcfftopdict ( SplineFont * sf , struct alltabs * at ) {
 char * pt , * end ;
 FILE * cfff = at -> cfff ;
 DBounds b ;
 putshort ( cfff , 1 ) ;
 putc ( '\2' , cfff ) ;
 putshort ( cfff , 1 ) ;
 at -> lenpos = ftell ( cfff ) ;
 putshort ( cfff , 0 ) ;
 dumpsid ( cfff , at , sf -> version , 0 ) ;
 dumpsid ( cfff , at , sf -> copyright , 1 ) ;
 dumpsid ( cfff , at , sf -> fullname ? sf -> fullname : sf -> fontname , 2 ) ;
 dumpsid ( cfff , at , sf -> familyname , 3 ) ;
 dumpsid ( cfff , at , sf -> weight , 4 ) ;
 if ( at -> gi . fixed_width > 0 ) dumpintoper ( cfff , 1 , ( 12 << 8 ) | 1 ) ;
 if ( sf -> italicangle != 0 ) dumpdbloper ( cfff , sf -> italicangle , ( 12 << 8 ) | 2 ) ;
 if ( sf -> upos != - 100 ) dumpdbloper ( cfff , sf -> upos , ( 12 << 8 ) | 3 ) ;
 if ( sf -> uwidth != 50 ) dumpdbloper ( cfff , sf -> uwidth , ( 12 << 8 ) | 4 ) ;
 if ( sf -> strokedfont ) {
 dumpintoper ( cfff , 2 , ( 12 << 8 ) | 5 ) ;
 dumpdbloper ( cfff , sf -> strokewidth , ( 12 << 8 ) | 8 ) ;
 }
 if ( sf -> ascent + sf -> descent != 1000 ) {
 dumpdbl ( cfff , 1.0 / ( sf -> ascent + sf -> descent ) ) ;
 dumpint ( cfff , 0 ) ;
 dumpint ( cfff , 0 ) ;
 dumpdbl ( cfff , 1.0 / ( sf -> ascent + sf -> descent ) ) ;
 dumpint ( cfff , 0 ) ;
 dumpintoper ( cfff , 0 , ( 12 << 8 ) | 7 ) ;
 }
 if ( sf -> uniqueid != - 1 && sf -> use_uniqueid ) dumpintoper ( cfff , sf -> uniqueid ? sf -> uniqueid : 4000000 + ( rand ( ) & 0x3ffff ) , 13 ) ;
 SplineFontLayerFindBounds ( sf , at -> gi . layer , & b ) ;
 at -> gi . xmin = b . minx ;
 at -> gi . ymin = b . miny ;
 at -> gi . xmax = b . maxx ;
 at -> gi . ymax = b . maxy ;
 dumpdbl ( cfff , floor ( b . minx ) ) ;
 dumpdbl ( cfff , floor ( b . miny ) ) ;
 dumpdbl ( cfff , ceil ( b . maxx ) ) ;
 dumpdbloper ( cfff , ceil ( b . maxy ) , 5 ) ;
 if ( sf -> xuid != NULL && sf -> use_xuid ) {
 pt = sf -> xuid ;
 if ( * pt == '[' ) ++ pt ;
 while ( * pt && * pt != ']' ) {
 dumpint ( cfff , strtol ( pt , & end , 10 ) ) ;
 if ( pt == end ) break ;
 for ( pt = end ;
 * pt == ' ' ;
 ++ pt ) ;
 }
 putc ( 14 , cfff ) ;
 if ( sf -> changed_since_xuidchanged ) SFIncrementXUID ( sf ) ;
 }
 }