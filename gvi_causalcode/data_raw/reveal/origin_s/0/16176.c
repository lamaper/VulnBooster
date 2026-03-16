static void dumpcffcidtopdict ( SplineFont * sf , struct alltabs * at ) {
 char * pt , * end ;
 FILE * cfff = at -> cfff ;
 DBounds b ;
 int cidcnt = 0 , k ;
 for ( k = 0 ;
 k < sf -> subfontcnt ;
 ++ k ) if ( sf -> subfonts [ k ] -> glyphcnt > cidcnt ) cidcnt = sf -> subfonts [ k ] -> glyphcnt ;
 putshort ( cfff , 1 ) ;
 putc ( '\2' , cfff ) ;
 putshort ( cfff , 1 ) ;
 at -> lenpos = ftell ( cfff ) ;
 putshort ( cfff , 0 ) ;
 dumpsid ( cfff , at , sf -> cidregistry , - 1 ) ;
 dumpsid ( cfff , at , sf -> ordering , - 1 ) ;
 dumpintoper ( cfff , sf -> supplement , ( 12 << 8 ) | 30 ) ;
 dumpdbloper ( cfff , sf -> cidversion , ( 12 << 8 ) | 31 ) ;
 dumpintoper ( cfff , cidcnt , ( 12 << 8 ) | 34 ) ;
 if ( sf -> use_uniqueid ) dumpintoper ( cfff , sf -> uniqueid ? sf -> uniqueid : 4000000 + ( rand ( ) & 0x3ffff ) , ( 12 << 8 ) | 35 ) ;
 dumpsid ( cfff , at , sf -> copyright , 1 ) ;
 dumpsid ( cfff , at , sf -> fullname ? sf -> fullname : sf -> fontname , 2 ) ;
 dumpsid ( cfff , at , sf -> familyname , 3 ) ;
 dumpsid ( cfff , at , sf -> weight , 4 ) ;
 CIDLayerFindBounds ( sf , at -> gi . layer , & b ) ;
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
 for ( pt = end ;
 * pt == ' ' ;
 ++ pt ) ;
 }
 putc ( 14 , cfff ) ;
 if ( sf -> changed_since_xuidchanged ) SFIncrementXUID ( sf ) ;
 }
 }