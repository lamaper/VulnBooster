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
 "schema" , required_argument , NULL , 'S' }
 , {
 "dbname" , required_argument , NULL , 'd' }
 , {
 "all" , no_argument , NULL , 'a' }
 , {
 "system" , no_argument , NULL , 's' }
 , {
 "table" , required_argument , NULL , 't' }
 , {
 "index" , required_argument , NULL , 'i' }
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
 const char * host = NULL ;
 const char * port = NULL ;
 const char * username = NULL ;
 enum trivalue prompt_password = TRI_DEFAULT ;
 bool syscatalog = false ;
 bool alldb = false ;
 bool echo = false ;
 bool quiet = false ;
 bool verbose = false ;
 SimpleStringList indexes = {
 NULL , NULL }
 ;
 SimpleStringList tables = {
 NULL , NULL }
 ;
 SimpleStringList schemas = {
 NULL , NULL }
 ;
 progname = get_progname ( argv [ 0 ] ) ;
 set_pglocale_pgservice ( argv [ 0 ] , PG_TEXTDOMAIN ( "pgscripts" ) ) ;
 handle_help_version_opts ( argc , argv , "reindexdb" , help ) ;
 while ( ( c = getopt_long ( argc , argv , "h:p:U:wWeqS:d:ast:i:v" , long_options , & optindex ) ) != - 1 ) {
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
 case 'S' : simple_string_list_append ( & schemas , optarg ) ;
 break ;
 case 'd' : dbname = pg_strdup ( optarg ) ;
 break ;
 case 'a' : alldb = true ;
 break ;
 case 's' : syscatalog = true ;
 break ;
 case 't' : simple_string_list_append ( & tables , optarg ) ;
 break ;
 case 'i' : simple_string_list_append ( & indexes , optarg ) ;
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
 fprintf ( stderr , _ ( "%s: cannot reindex all databases and a specific one at the same time\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 if ( syscatalog ) {
 fprintf ( stderr , _ ( "%s: cannot reindex all databases and system catalogs at the same time\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 if ( schemas . head != NULL ) {
 fprintf ( stderr , _ ( "%s: cannot reindex specific schema(s) in all databases\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 if ( tables . head != NULL ) {
 fprintf ( stderr , _ ( "%s: cannot reindex specific table(s) in all databases\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 if ( indexes . head != NULL ) {
 fprintf ( stderr , _ ( "%s: cannot reindex specific index(es) in all databases\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 reindex_all_databases ( maintenance_db , host , port , username , prompt_password , progname , echo , quiet , verbose ) ;
 }
 else if ( syscatalog ) {
 if ( schemas . head != NULL ) {
 fprintf ( stderr , _ ( "%s: cannot reindex specific schema(s) and system catalogs at the same time\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 if ( tables . head != NULL ) {
 fprintf ( stderr , _ ( "%s: cannot reindex specific table(s) and system catalogs at the same time\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 if ( indexes . head != NULL ) {
 fprintf ( stderr , _ ( "%s: cannot reindex specific index(es) and system catalogs at the same time\n" ) , progname ) ;
 exit ( 1 ) ;
 }
 if ( dbname == NULL ) {
 if ( getenv ( "PGDATABASE" ) ) dbname = getenv ( "PGDATABASE" ) ;
 else if ( getenv ( "PGUSER" ) ) dbname = getenv ( "PGUSER" ) ;
 else dbname = get_user_name_or_exit ( progname ) ;
 }
 reindex_system_catalogs ( dbname , host , port , username , prompt_password , progname , echo , verbose ) ;
 }
 else {
 if ( dbname == NULL ) {
 if ( getenv ( "PGDATABASE" ) ) dbname = getenv ( "PGDATABASE" ) ;
 else if ( getenv ( "PGUSER" ) ) dbname = getenv ( "PGUSER" ) ;
 else dbname = get_user_name_or_exit ( progname ) ;
 }
 if ( schemas . head != NULL ) {
 SimpleStringListCell * cell ;
 for ( cell = schemas . head ;
 cell ;
 cell = cell -> next ) {
 reindex_one_database ( cell -> val , dbname , "SCHEMA" , host , port , username , prompt_password , progname , echo , verbose ) ;
 }
 }
 if ( indexes . head != NULL ) {
 SimpleStringListCell * cell ;
 for ( cell = indexes . head ;
 cell ;
 cell = cell -> next ) {
 reindex_one_database ( cell -> val , dbname , "INDEX" , host , port , username , prompt_password , progname , echo , verbose ) ;
 }
 }
 if ( tables . head != NULL ) {
 SimpleStringListCell * cell ;
 for ( cell = tables . head ;
 cell ;
 cell = cell -> next ) {
 reindex_one_database ( cell -> val , dbname , "TABLE" , host , port , username , prompt_password , progname , echo , verbose ) ;
 }
 }
 if ( indexes . head == NULL && tables . head == NULL && schemas . head == NULL ) reindex_one_database ( NULL , dbname , "DATABASE" , host , port , username , prompt_password , progname , echo , verbose ) ;
 }
 exit ( 0 ) ;
 }