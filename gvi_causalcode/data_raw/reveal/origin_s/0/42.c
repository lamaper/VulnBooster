static void report_progress ( const MYSQL * mysql , uint stage , uint max_stage , double progress , const char * proc_info , uint proc_info_length ) {
 uint length = printf ( "Stage: %d of %d '%.*s' %6.3g%% of stage done" , stage , max_stage , proc_info_length , proc_info , progress ) ;
 if ( length < last_progress_report_length ) printf ( "%*s" , last_progress_report_length - length , "" ) ;
 putc ( '\r' , stdout ) ;
 fflush ( stdout ) ;
 last_progress_report_length = length ;
 }