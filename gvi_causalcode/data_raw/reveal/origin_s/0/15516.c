static void redohhead ( struct alltabs * at , int isv ) {
 int i ;
 struct hhead * head ;
 FILE * f ;
 if ( ! isv ) {
 f = at -> hheadf = tmpfile ( ) ;
 head = & at -> hhead ;
 }
 else {
 f = at -> vheadf = tmpfile ( ) ;
 head = & at -> vhead ;
 }
 putlong ( f , head -> version ) ;
 putshort ( f , head -> ascender ) ;
 putshort ( f , head -> descender ) ;
 putshort ( f , head -> linegap ) ;
 putshort ( f , head -> maxwidth ) ;
 putshort ( f , head -> minlsb ) ;
 putshort ( f , head -> minrsb ) ;
 putshort ( f , head -> maxextent ) ;
 putshort ( f , head -> caretSlopeRise ) ;
 putshort ( f , head -> caretSlopeRun ) ;
 for ( i = 0 ;
 i < 5 ;
 ++ i ) putshort ( f , head -> mbz [ i ] ) ;
 putshort ( f , head -> metricformat ) ;
 putshort ( f , head -> numMetrics ) ;
 if ( ! isv ) {
 at -> hheadlen = ftell ( f ) ;
 if ( ( at -> hheadlen & 2 ) != 0 ) putshort ( f , 0 ) ;
 }
 else {
 at -> vheadlen = ftell ( f ) ;
 if ( ( at -> vheadlen & 2 ) != 0 ) putshort ( f , 0 ) ;
 }
 }