static void report_progress_end ( ) {
 if ( last_progress_report_length ) {
 printf ( "%*s\r" , last_progress_report_length , "" ) ;
 last_progress_report_length = 0 ;
 }
 }