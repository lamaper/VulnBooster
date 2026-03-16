static bool _sched_backfill ( void ) {
 static int backfill = - 1 ;
 if ( backfill == - 1 ) {
 char * sched_type = slurm_get_sched_type ( ) ;
 if ( ! xstrcmp ( sched_type , "sched/backfill" ) ) backfill = 1 ;
 else backfill = 0 ;
 xfree ( sched_type ) ;
 }
 if ( backfill ) return true ;
 return false ;
 }