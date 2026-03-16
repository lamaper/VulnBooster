int main ( int argc , char * argv [ ] ) {
 static struct option long_options [ ] = {
 {
 "host" , required_argument , NULL , 'h' }
 , {
 "port" , required_argument , NULL , 'p' }
 , {
 "username" , required_argument , NULL , 'U' }
 , {
 "no-password" , no_argument , NULL , 'w' }
 , {
 "password" , no_argument , NULL , 'W' }
 , {
 "echo" , no_argument , NULL , 'e' }
 , {
 "quiet" , no_argument , NULL , 'q' }
 , {
 "dbname" , required_argument , NULL , 'd' }
 , {
 "analyze" , no_argument , NULL , 'z' }
 , {
 "analyze-only" , no_argument , NULL , 'Z' }
 , {
 "freeze" , no_argument , NULL , 'F' }
 , {
 "all" , no_argument , NULL , 'a' }
 , {
 "table" , required_argument , NULL , 't' }
 , {
 "full" , no_argument , NULL , 'f' }
 , {
 "verbose" , no_argument , NULL , 'v' }
 , {
 "jobs" , required_argument , NULL , 'j' }
 , {
 "maintenance-db" , required_argument , NULL , 2 }
 , {
 "analyze-in-stages" , no_argument , NULL , 3 }
 , {
 NULL , 0 , NULL , 0 }
 }
 ;
 const char * progname ;
 int optindex ;
 int c ;
 const char * dbname = NULL ;
 const char * maintenance_db = NULL ;
 char * host = NULL ;
 char * port = NULL ;
 char * username = NULL ;
 enum trivalue prompt_password = TRI_DEFAULT ;
 bool echo = false ;
 bool quiet = false ;
 vacuumingOptions vacopts ;
 bool analyze_in_stages = false ;
 bool alldb = false ;
 SimpleStringList tables = {
 NULL , NULL }
 ;
 int concurrentCons = 1 ;
 int tbl_count = 0 ;
 memset ( & vacopts , 0 , sizeof ( vacopts ) ) ;
 progname = get_progname ( argv [ 0 ] ) ;
 set_pglocale_pgservice ( argv [ 0 ] , PG_TEXTDOMAIN ( "pgscripts" ) ) ;
 handle_help_version_opts ( argc , argv , "vacuumdb" , help ) ;
 while ( ( c = getopt_long ( argc , argv , "h:p:U:wWeqd:zZFat:fvj:" , long_options , & optindex ) ) != - 1 ) {
 switch ( c ) {
 case 'h' : host = pg_strdup ( optarg ) ;
 break ;
 case 'p' : port = pg_strdup ( optarg ) ;
 break ;
 case 'U' : username = pg_strdup ( optarg ) ;
 break ;
 case 'w' : prompt_password = TRI_NO ;
 break ;
 case 'W' : prompt_password = TRI_YES ;
 break ;
 case 'e' : echo = true ;
 break ;
 case 'q' : quiet = true ;
 break ;
 case 'd' : dbname = pg_strdup ( optarg ) ;
 break ;
 case 'z' : vacopts . and_analyze = true ;
 break ;
 case 'Z' : vacopts . analyze_only = true ;
 break ;
 case 'F' : vacopts . freeze = true ;
 break ;
 case 'a' : alldb = true ;
 break ;
 case 't' : {
 simple_string_list_append ( & tables , optarg ) ;
 tbl_count ++ ;
 break ;
 }
 case 'f' : vacopts . full = true ;
 break ;
 case 'v' : vacopts . verbose = true ;
 break ;
 case 'j' : concurrentCons = atoi ( optarg ) ;
 if ( concurrentCons <= 0 ) {
 fprintf ( stderr , _ ( "%s: number of parallel jobs must be at least 1\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 if ( concurrentCons > FD_SETSIZE - 1 ) {
 fprintf ( stderr , _ ( "%s: too many parallel jobs requested (maximum: %d)\n" ) , progname , FD_SETSIZE - 1 ) ;
 exit ( 1 ) ;
 }
 break ;
 case 2 : maintenance_db = pg_strdup ( optarg ) ;
 break ;
 case 3 : analyze_in_stages = vacopts . analyze_only = true ;
 break ;
 default : fprintf ( stderr , _ ( "Try \"%s --help\" for more information.\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 }
 if ( optind < argc && dbname == NULL ) {
 dbname = argv [ optind ] ;
 optind ++ ;
 }
 if ( optind < argc ) {
 fprintf ( stderr , _ ( "%s: too many command-line arguments (first is \"%s\")\n" ) , progname , argv [ optind ] ) ;
 fprintf ( stderr , _ ( "Try \"%s --help\" for more information.\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 if ( vacopts . analyze_only ) {
 if ( vacopts . full ) {
 fprintf ( stderr , _ ( "%s: cannot use the \"%s\" option when performing only analyze\n" ) , progname , "full" ) ;
 exit ( 1 ) ;
 }
 if ( vacopts . freeze ) {
 fprintf ( stderr , _ ( "%s: cannot use the \"%s\" option when performing only analyze\n" ) , progname , "freeze" ) ;
 exit ( 1 ) ;
 }
 }
 setup_cancel_handler ( ) ;
 if ( tbl_count && ( concurrentCons > tbl_count ) ) concurrentCons = tbl_count ;
 if ( alldb ) {
 if ( dbname ) {
 fprintf ( stderr , _ ( "%s: cannot vacuum all databases and a specific one at the same time\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 if ( tables . head != NULL ) {
 fprintf ( stderr , _ ( "%s: cannot vacuum specific table(s) in all databases\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 vacuum_all_databases ( & vacopts , analyze_in_stages , maintenance_db , host , port , username , prompt_password , concurrentCons , progname , echo , quiet ) ;
 }
 else {
 if ( dbname == NULL ) {
 if ( getenv ( "PGDATABASE" ) ) dbname = getenv ( "PGDATABASE" ) ;
 else if ( getenv ( "PGUSER" ) ) dbname = getenv ( "PGUSER" ) ;
 else dbname = get_user_name_or_exit ( progname ) ;
 }
 if ( analyze_in_stages ) {
 int stage ;
 for ( stage = 0 ;
 stage < ANALYZE_NUM_STAGES ;
 stage ++ ) {
 vacuum_one_database ( dbname , & vacopts , stage , & tables , host , port , username , prompt_password , concurrentCons , progname , echo , quiet ) ;
 }
 }
 else vacuum_one_database ( dbname , & vacopts , ANALYZE_NO_STAGE , & tables , host , port , username , prompt_password , concurrentCons , progname , echo , quiet ) ;
 }
 exit ( 0 ) ;
 }