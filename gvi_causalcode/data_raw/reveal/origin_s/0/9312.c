static void dumpgasp ( struct alltabs * at , SplineFont * sf ) {
 int i ;
 at -> gaspf = tmpfile ( ) ;
 if ( sf -> gasp_cnt == 0 ) {
 putshort ( at -> gaspf , 0 ) ;
 putshort ( at -> gaspf , 1 ) ;
 putshort ( at -> gaspf , 0xffff ) ;
 putshort ( at -> gaspf , 0x2 ) ;
 }
 else {
 putshort ( at -> gaspf , sf -> gasp_version ) ;
 putshort ( at -> gaspf , sf -> gasp_cnt ) ;
 for ( i = 0 ;
 i < sf -> gasp_cnt ;
 ++ i ) {
 putshort ( at -> gaspf , sf -> gasp [ i ] . ppem ) ;
 putshort ( at -> gaspf , sf -> gasp [ i ] . flags ) ;
 }
 }
 at -> gasplen = ftell ( at -> gaspf ) ;
 }