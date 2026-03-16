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
 "all" , no_argument , NULL , 'a' }
 , {
 "table" , required_argument , NULL , 't' }
 , {
 "verbose" , no_argument , NULL , 'v' }
 , {
 "maintenance-db" , required_argument , NULL , 2 }
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
 bool alldb = false ;
 bool verbose = false ;
 SimpleStringList tables = {
 NULL , NULL }
 ;
 progname = get_progname ( argv [ 0 ] ) ;
 set_pglocale_pgservice ( argv [ 0 ] , PG_TEXTDOMAIN ( "pgscripts" ) ) ;
 handle_help_version_opts ( argc , argv , "clusterdb" , help ) ;
 while ( ( c = getopt_long ( argc , argv , "h:p:U:wWeqd:at:v" , long_options , & optindex ) ) != - 1 ) {
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
 case 'a' : alldb = true ;
 break ;
 case 't' : simple_string_list_append ( & tables , optarg ) ;
 break ;
 case 'v' : verbose = true ;
 break ;
 case 2 : maintenance_db = pg_strdup ( optarg ) ;
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
 setup_cancel_handler ( ) ;
 if ( alldb ) {
 if ( dbname ) {
 fprintf ( stderr , _ ( "%s: cannot cluster all databases and a specific one at the same time\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 if ( tables . head != NULL ) {
 fprintf ( stderr , _ ( "%s: cannot cluster specific table(s) in all databases\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 cluster_all_databases ( verbose , maintenance_db , host , port , username , prompt_password , progname , echo , quiet ) ;
 }
 else {
 if ( dbname == NULL ) {
 if ( getenv ( "PGDATABASE" ) ) dbname = getenv ( "PGDATABASE" ) ;
 else if ( getenv ( "PGUSER" ) ) dbname = getenv ( "PGUSER" ) ;
 else dbname = get_user_name_or_exit ( progname ) ;
 }
 if ( tables . head != NULL ) {
 SimpleStringListCell * cell ;
 for ( cell = tables . head ;
 cell ;
 cell = cell -> next ) {
 cluster_one_database ( dbname , verbose , cell -> val , host , port , username , prompt_password , progname , echo ) ;
 }
 }
 else cluster_one_database ( dbname , verbose , NULL , host , port , username , prompt_password , progname , echo ) ;
 }
 exit ( 0 ) ;
 }