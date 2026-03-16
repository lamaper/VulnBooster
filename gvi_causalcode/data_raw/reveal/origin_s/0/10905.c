static RETSIGTYPE die ( int killed ) {
 static TERMIO sgtty ;
 if ( killed != 0 ) {
 STTY ( 0 , & sgtty ) ;
 }
 else {
 GTTY ( 0 , & sgtty ) ;
 }
 if ( killed != 0 ) {
 _exit ( 128 + killed ) ;
 }
 }