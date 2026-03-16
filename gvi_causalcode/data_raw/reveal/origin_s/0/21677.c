static int dumpcffdict ( SplineFont * sf , struct alltabs * at ) {
 FILE * fdarray = at -> fdarray ;
 int pstart ;
 dumpsid ( fdarray , at , sf -> fontname , ( 12 << 8 ) | 38 ) ;
 if ( sf -> ascent + sf -> descent != 1000 ) {
 dumpdbl ( fdarray , 1.0 / ( sf -> ascent + sf -> descent ) ) ;
 dumpint ( fdarray , 0 ) ;
 dumpint ( fdarray , 0 ) ;
 dumpdbl ( fdarray , 1.0 / ( sf -> ascent + sf -> descent ) ) ;
 dumpint ( fdarray , 0 ) ;
 dumpintoper ( fdarray , 0 , ( 12 << 8 ) | 7 ) ;
 }
 pstart = ftell ( fdarray ) ;
 dumpsizedint ( fdarray , false , 0 , - 1 ) ;
 dumpsizedint ( fdarray , true , 0 , 18 ) ;
 return ( pstart ) ;
 }