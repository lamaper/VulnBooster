void write_stats ( void ) {
 FILE * fp ;





 prio_set = 0 ;
 o_prio = getpriority ( PRIO_PROCESS , 0 ) ;
 if ( ( errno == 0 ) && ( setpriority ( PRIO_PROCESS , 0 , - 20 ) == 0 ) ) prio_set = 1 ;

 tv . tv_sec = ts . tv_sec ;
 tv . tv_usec = ts . tv_nsec / 1000 ;




 if ( stats_drift_file != 0 ) {


 wander_resid *= 0.5 ;
 return ;
 }
 prev_drift_comp = drift_comp ;
 wander_resid = wander_threshold ;
 if ( ( fp = fopen ( stats_temp_file , "w" ) ) == NULL ) {
 msyslog ( LOG_ERR , "frequency file %s: %m" , stats_temp_file ) ;
 return ;
 }
 fprintf ( fp , "%.3f\n" , drift_comp * 1e6 ) ;
 ( void ) fclose ( fp ) ;



 msyslog ( LOG_ERR , "frequency file %s: %m" , stats_drift_file ) ;
 return ;
 }

 $DESCRIPTOR ( oldvers , ";
-1" ) ;
 struct dsc$descriptor driftdsc = {
 strlen ( stats_drift_file ) , 0 , 0 , stats_drift_file }
 ;
 while ( lib$delete_file ( & oldvers , & driftdsc ) & 1 ) ;
 }

 }