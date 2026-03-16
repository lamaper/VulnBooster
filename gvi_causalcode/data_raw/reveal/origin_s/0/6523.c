int tm_adopt ( char * id , int adoptCmd , pid_t pid ) {
 int rc = TM_SUCCESS ;
 int status , ret ;
 pid_t sid ;
 char * env ;
 struct tcp_chan * chan = NULL ;
 sid = getsid ( pid ) ;
 if ( ! ispidowner ( sid ) ) return ( TM_EPERM ) ;
 if ( init_done ) return TM_BADINIT ;
 init_done = 1 ;
 if ( ( tm_jobid = getenv ( "PBS_JOBID" ) ) == NULL ) tm_jobid = ( char * ) "ADOPT JOB" ;
 tm_jobid_len = strlen ( tm_jobid ) ;
 if ( ( tm_jobcookie = getenv ( "PBS_JOBCOOKIE" ) ) == NULL ) tm_jobcookie = ( char * ) "ADOPT COOKIE" ;
 tm_jobcookie_len = strlen ( tm_jobcookie ) ;
 tm_jobndid = 0 ;
 tm_jobtid = 0 ;
 if ( ( env = getenv ( "PBS_MOMPORT" ) ) == NULL || ( tm_momport = atoi ( env ) ) == 0 ) tm_momport = PBS_MANAGER_SERVICE_PORT ;
 if ( adoptCmd != TM_ADOPT_ALTID && adoptCmd != TM_ADOPT_JOBID ) return TM_EUNKNOWNCMD ;
 if ( startcom ( adoptCmd , TM_NULL_EVENT , & chan ) != DIS_SUCCESS ) return TM_ESYSTEM ;
 if ( diswsi ( chan , sid ) != DIS_SUCCESS ) {
 rc = TM_ENOTCONNECTED ;
 goto tm_adopt_cleanup ;
 }
 if ( diswsi ( chan , pid ) != DIS_SUCCESS ) {
 rc = TM_ENOTCONNECTED ;
 goto tm_adopt_cleanup ;
 }
 if ( diswcs ( chan , id , strlen ( id ) ) != DIS_SUCCESS ) {
 rc = TM_ENOTCONNECTED ;
 goto tm_adopt_cleanup ;
 }
 DIS_tcp_wflush ( chan ) ;
 status = disrsi ( chan , & ret ) ;
 if ( ret != DIS_SUCCESS ) {
 rc = TM_ENOTCONNECTED ;
 goto tm_adopt_cleanup ;
 }
 tm_finalize ( ) ;
 if ( local_conn > - 1 ) {
 close ( local_conn ) ;
 local_conn = - 1 ;
 }
 DIS_tcp_cleanup ( chan ) ;
 return ( status == TM_OKAY ? TM_SUCCESS : TM_ENOTFOUND ) ;
 tm_adopt_cleanup : if ( chan != NULL ) DIS_tcp_cleanup ( chan ) ;
 return rc ;
 }