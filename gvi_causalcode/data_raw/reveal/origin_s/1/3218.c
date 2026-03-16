int main ( int argc , char * * argv ) {
 int ArgIndex ;
 int NumErrs = 0 ;
 char * Args [ MAXARGS ] ;
 int aindex = 0 ;
 int rc ;
 int pid ;
 char tmpJobID [ PBS_MAXCLTJOBID ] ;
 char JobID [ PBS_MAXCLTJOBID ] ;
 char ServerName [ MAXSERVERNAME ] ;
 int DoBackground = 0 ;
 tmpJobID [ 0 ] = '\0' ;

 switch ( ArgIndex ) {
 case 'b' : DoBackground = 1 ;
 break ;
 case 'j' : strncpy ( tmpJobID , optarg , sizeof ( tmpJobID ) ) ;
 if ( tmpJobID [ PBS_MAXCLTJOBID - 1 ] != '\0' ) {
 fprintf ( stderr , "pbs_track: given job ID too large (> %d)\n" , PBS_MAXCLTJOBID ) ;
 exit ( - 1 ) ;
 }
 break ;
 default : NumErrs ++ ;
 break ;
 }
 }
 if ( ( NumErrs > 0 ) || ( optind >= argc ) || ( tmpJobID [ 0 ] == '\0' ) ) {
 static char Usage [ ] = "USAGE: pbs_track [-j <JOBID>] [-b] -- a.out arg1 arg2 ... argN\n" ;
 fprintf ( stderr , "%s" , Usage ) ;
 exit ( 2 ) ;
 }
 if ( getenv ( NO_SERVER_SUFFIX ) != NULL ) {
 snprintf ( JobID , sizeof ( JobID ) , "%s" , tmpJobID ) ;
 }
 else {
 if ( get_server ( tmpJobID , JobID , sizeof ( JobID ) , ServerName , sizeof ( ServerName ) ) ) {
 fprintf ( stderr , "pbs_track: illegally formed job identifier: '%s'\n" , JobID ) ;
 exit ( 1 ) ;
 }
 }
 aindex = 0 ;
 for ( ;
 optind < argc ;
 optind ++ ) {
 Args [ aindex ++ ] = strdup ( argv [ optind ] ) ;
 printf ( "Got arg: %s\n" , Args [ aindex - 1 ] ) ;
 }
 Args [ aindex ] = NULL ;
 pid = 1 ;
 if ( DoBackground == 1 ) {
 printf ( "FORKING!\n" ) ;
 pid = fork ( ) ;
 }
 if ( ( DoBackground == 0 ) || ( pid == 0 ) ) {
 rc = tm_adopt ( JobID , TM_ADOPT_JOBID , getpid ( ) ) ;
 switch ( rc ) {
 case TM_SUCCESS : break ;
 case TM_ENOTFOUND : fprintf ( stderr , "pbs_track: MOM could not find job %s\n" , JobID ) ;
 break ;
 case TM_ESYSTEM : case TM_ENOTCONNECTED : fprintf ( stderr , "pbs_track: error occurred while trying to communication with pbs_mom: %s (%d)\n" , pbse_to_txt ( rc ) , rc ) ;
 break ;
 default : fprintf ( stderr , "pbs_track: unexpected error %s (%d) occurred\n" , pbse_to_txt ( rc ) , rc ) ;
 break ;
 }
 if ( rc != TM_SUCCESS ) {
 exit ( - 1 ) ;
 }
 if ( execvp ( Args [ 0 ] , Args ) == - 1 ) {
 fprintf ( stderr , "execvp failed with error %d, message:\n%s\n" , errno , strerror ( errno ) ) ;
 }
 }
 else if ( pid > 0 ) {
 fclose ( stdin ) ;
 fclose ( stdout ) ;
 fclose ( stderr ) ;
 }
 else if ( pid < 0 ) {
 fprintf ( stderr , "pbs_track: could not fork (%d:%s)\n" , errno , strerror ( errno ) ) ;
 }
 exit ( 0 ) ;
 }