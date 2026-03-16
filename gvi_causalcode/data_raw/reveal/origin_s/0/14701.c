int main ( int argc , char * argv [ ] ) {
 static struct option long_options [ ] = {
 {
 "data-only" , no_argument , NULL , 'a' }
 , {
 "clean" , no_argument , NULL , 'c' }
 , {
 "file" , required_argument , NULL , 'f' }
 , {
 "globals-only" , no_argument , NULL , 'g' }
 , {
 "host" , required_argument , NULL , 'h' }
 , {
 "dbname" , required_argument , NULL , 'd' }
 , {
 "database" , required_argument , NULL , 'l' }
 , {
 "oids" , no_argument , NULL , 'o' }
 , {
 "no-owner" , no_argument , NULL , 'O' }
 , {
 "port" , required_argument , NULL , 'p' }
 , {
 "roles-only" , no_argument , NULL , 'r' }
 , {
 "schema-only" , no_argument , NULL , 's' }
 , {
 "superuser" , required_argument , NULL , 'S' }
 , {
 "tablespaces-only" , no_argument , NULL , 't' }
 , {
 "username" , required_argument , NULL , 'U' }
 , {
 "verbose" , no_argument , NULL , 'v' }
 , {
 "no-password" , no_argument , NULL , 'w' }
 , {
 "password" , no_argument , NULL , 'W' }
 , {
 "no-privileges" , no_argument , NULL , 'x' }
 , {
 "no-acl" , no_argument , NULL , 'x' }
 , {
 "attribute-inserts" , no_argument , & column_inserts , 1 }
 , {
 "binary-upgrade" , no_argument , & binary_upgrade , 1 }
 , {
 "column-inserts" , no_argument , & column_inserts , 1 }
 , {
 "disable-dollar-quoting" , no_argument , & disable_dollar_quoting , 1 }
 , {
 "disable-triggers" , no_argument , & disable_triggers , 1 }
 , {
 "if-exists" , no_argument , & if_exists , 1 }
 , {
 "inserts" , no_argument , & inserts , 1 }
 , {
 "lock-wait-timeout" , required_argument , NULL , 2 }
 , {
 "no-tablespaces" , no_argument , & no_tablespaces , 1 }
 , {
 "quote-all-identifiers" , no_argument , & quote_all_identifiers , 1 }
 , {
 "role" , required_argument , NULL , 3 }
 , {
 "use-set-session-authorization" , no_argument , & use_setsessauth , 1 }
 , {
 "no-security-labels" , no_argument , & no_security_labels , 1 }
 , {
 "no-unlogged-table-data" , no_argument , & no_unlogged_table_data , 1 }
 , {
 NULL , 0 , NULL , 0 }
 }
 ;
 char * pghost = NULL ;
 char * pgport = NULL ;
 char * pguser = NULL ;
 char * pgdb = NULL ;
 char * use_role = NULL ;
 trivalue prompt_password = TRI_DEFAULT ;
 bool data_only = false ;
 bool globals_only = false ;
 bool output_clean = false ;
 bool roles_only = false ;
 bool tablespaces_only = false ;
 PGconn * conn ;
 int encoding ;
 const char * std_strings ;
 int c , ret ;
 int optindex ;
 set_pglocale_pgservice ( argv [ 0 ] , PG_TEXTDOMAIN ( "pg_dump" ) ) ;
 progname = get_progname ( argv [ 0 ] ) ;
 if ( argc > 1 ) {
 if ( strcmp ( argv [ 1 ] , "--help" ) == 0 || strcmp ( argv [ 1 ] , "-?" ) == 0 ) {
 help ( ) ;
 exit_nicely ( 0 ) ;
 }
 if ( strcmp ( argv [ 1 ] , "--version" ) == 0 || strcmp ( argv [ 1 ] , "-V" ) == 0 ) {
 puts ( "pg_dumpall (PostgreSQL) " PG_VERSION ) ;
 exit_nicely ( 0 ) ;
 }
 }
 if ( ( ret = find_other_exec ( argv [ 0 ] , "pg_dump" , PGDUMP_VERSIONSTR , pg_dump_bin ) ) < 0 ) {
 char full_path [ MAXPGPATH ] ;
 if ( find_my_exec ( argv [ 0 ] , full_path ) < 0 ) strlcpy ( full_path , progname , sizeof ( full_path ) ) ;
 if ( ret == - 1 ) fprintf ( stderr , _ ( "The program \"pg_dump\" is needed by %s " "but was not found in the\n" "same directory as \"%s\".\n" "Check your installation.\n" ) , progname , full_path ) ;
 else fprintf ( stderr , _ ( "The program \"pg_dump\" was found by \"%s\"\n" "but was not the same version as %s.\n" "Check your installation.\n" ) , full_path , progname ) ;
 exit_nicely ( 1 ) ;
 }
 pgdumpopts = createPQExpBuffer ( ) ;
 while ( ( c = getopt_long ( argc , argv , "acd:f:gh:l:oOp:rsS:tU:vwWx" , long_options , & optindex ) ) != - 1 ) {
 switch ( c ) {
 case 'a' : data_only = true ;
 appendPQExpBufferStr ( pgdumpopts , " -a" ) ;
 break ;
 case 'c' : output_clean = true ;
 break ;
 case 'd' : connstr = pg_strdup ( optarg ) ;
 break ;
 case 'f' : filename = pg_strdup ( optarg ) ;
 appendPQExpBufferStr ( pgdumpopts , " -f " ) ;
 appendShellString ( pgdumpopts , filename ) ;
 break ;
 case 'g' : globals_only = true ;
 break ;
 case 'h' : pghost = pg_strdup ( optarg ) ;
 break ;
 case 'l' : pgdb = pg_strdup ( optarg ) ;
 break ;
 case 'o' : appendPQExpBufferStr ( pgdumpopts , " -o" ) ;
 break ;
 case 'O' : appendPQExpBufferStr ( pgdumpopts , " -O" ) ;
 break ;
 case 'p' : pgport = pg_strdup ( optarg ) ;
 break ;
 case 'r' : roles_only = true ;
 break ;
 case 's' : appendPQExpBufferStr ( pgdumpopts , " -s" ) ;
 break ;
 case 'S' : appendPQExpBufferStr ( pgdumpopts , " -S " ) ;
 appendShellString ( pgdumpopts , optarg ) ;
 break ;
 case 't' : tablespaces_only = true ;
 break ;
 case 'U' : pguser = pg_strdup ( optarg ) ;
 break ;
 case 'v' : verbose = true ;
 appendPQExpBufferStr ( pgdumpopts , " -v" ) ;
 break ;
 case 'w' : prompt_password = TRI_NO ;
 appendPQExpBufferStr ( pgdumpopts , " -w" ) ;
 break ;
 case 'W' : prompt_password = TRI_YES ;
 appendPQExpBufferStr ( pgdumpopts , " -W" ) ;
 break ;
 case 'x' : skip_acls = true ;
 appendPQExpBufferStr ( pgdumpopts , " -x" ) ;
 break ;
 case 0 : break ;
 case 2 : appendPQExpBufferStr ( pgdumpopts , " --lock-wait-timeout " ) ;
 appendShellString ( pgdumpopts , optarg ) ;
 break ;
 case 3 : use_role = pg_strdup ( optarg ) ;
 appendPQExpBufferStr ( pgdumpopts , " --role " ) ;
 appendShellString ( pgdumpopts , use_role ) ;
 break ;
 default : fprintf ( stderr , _ ( "Try \"%s --help\" for more information.\n" ) , progname ) ;
 exit_nicely ( 1 ) ;
 }
 }
 if ( optind < argc ) {
 fprintf ( stderr , _ ( "%s: too many command-line arguments (first is \"%s\")\n" ) , progname , argv [ optind ] ) ;
 fprintf ( stderr , _ ( "Try \"%s --help\" for more information.\n" ) , progname ) ;
 exit_nicely ( 1 ) ;
 }
 if ( globals_only && roles_only ) {
 fprintf ( stderr , _ ( "%s: options -g/--globals-only and -r/--roles-only cannot be used together\n" ) , progname ) ;
 fprintf ( stderr , _ ( "Try \"%s --help\" for more information.\n" ) , progname ) ;
 exit_nicely ( 1 ) ;
 }
 if ( globals_only && tablespaces_only ) {
 fprintf ( stderr , _ ( "%s: options -g/--globals-only and -t/--tablespaces-only cannot be used together\n" ) , progname ) ;
 fprintf ( stderr , _ ( "Try \"%s --help\" for more information.\n" ) , progname ) ;
 exit_nicely ( 1 ) ;
 }
 if ( if_exists && ! output_clean ) {
 fprintf ( stderr , _ ( "%s: option --if-exists requires option -c/--clean\n" ) , progname ) ;
 exit_nicely ( 1 ) ;
 }
 if ( roles_only && tablespaces_only ) {
 fprintf ( stderr , _ ( "%s: options -r/--roles-only and -t/--tablespaces-only cannot be used together\n" ) , progname ) ;
 fprintf ( stderr , _ ( "Try \"%s --help\" for more information.\n" ) , progname ) ;
 exit_nicely ( 1 ) ;
 }
 if ( binary_upgrade ) appendPQExpBufferStr ( pgdumpopts , " --binary-upgrade" ) ;
 if ( column_inserts ) appendPQExpBufferStr ( pgdumpopts , " --column-inserts" ) ;
 if ( disable_dollar_quoting ) appendPQExpBufferStr ( pgdumpopts , " --disable-dollar-quoting" ) ;
 if ( disable_triggers ) appendPQExpBufferStr ( pgdumpopts , " --disable-triggers" ) ;
 if ( inserts ) appendPQExpBufferStr ( pgdumpopts , " --inserts" ) ;
 if ( no_tablespaces ) appendPQExpBufferStr ( pgdumpopts , " --no-tablespaces" ) ;
 if ( quote_all_identifiers ) appendPQExpBufferStr ( pgdumpopts , " --quote-all-identifiers" ) ;
 if ( use_setsessauth ) appendPQExpBufferStr ( pgdumpopts , " --use-set-session-authorization" ) ;
 if ( no_security_labels ) appendPQExpBufferStr ( pgdumpopts , " --no-security-labels" ) ;
 if ( no_unlogged_table_data ) appendPQExpBufferStr ( pgdumpopts , " --no-unlogged-table-data" ) ;
 if ( pgdb ) {
 conn = connectDatabase ( pgdb , connstr , pghost , pgport , pguser , prompt_password , false ) ;
 if ( ! conn ) {
 fprintf ( stderr , _ ( "%s: could not connect to database \"%s\"\n" ) , progname , pgdb ) ;
 exit_nicely ( 1 ) ;
 }
 }
 else {
 conn = connectDatabase ( "postgres" , connstr , pghost , pgport , pguser , prompt_password , false ) ;
 if ( ! conn ) conn = connectDatabase ( "template1" , connstr , pghost , pgport , pguser , prompt_password , true ) ;
 if ( ! conn ) {
 fprintf ( stderr , _ ( "%s: could not connect to databases \"postgres\" or \"template1\"\n" "Please specify an alternative database.\n" ) , progname ) ;
 fprintf ( stderr , _ ( "Try \"%s --help\" for more information.\n" ) , progname ) ;
 exit_nicely ( 1 ) ;
 }
 }
 if ( filename ) {
 OPF = fopen ( filename , PG_BINARY_W ) ;
 if ( ! OPF ) {
 fprintf ( stderr , _ ( "%s: could not open the output file \"%s\": %s\n" ) , progname , filename , strerror ( errno ) ) ;
 exit_nicely ( 1 ) ;
 }
 }
 else OPF = stdout ;
 encoding = PQclientEncoding ( conn ) ;
 std_strings = PQparameterStatus ( conn , "standard_conforming_strings" ) ;
 if ( ! std_strings ) std_strings = "off" ;
 if ( use_role && server_version >= 80100 ) {
 PQExpBuffer query = createPQExpBuffer ( ) ;
 appendPQExpBuffer ( query , "SET ROLE %s" , fmtId ( use_role ) ) ;
 executeCommand ( conn , query -> data ) ;
 destroyPQExpBuffer ( query ) ;
 }
 if ( quote_all_identifiers && server_version >= 90100 ) executeCommand ( conn , "SET quote_all_identifiers = true" ) ;
 fprintf ( OPF , "--\n-- PostgreSQL database cluster dump\n--\n\n" ) ;
 if ( verbose ) dumpTimestamp ( "Started on" ) ;
 fprintf ( OPF , "SET default_transaction_read_only = off;
\n\n" ) ;
 fprintf ( OPF , "SET client_encoding = '%s';
\n" , pg_encoding_to_char ( encoding ) ) ;
 fprintf ( OPF , "SET standard_conforming_strings = %s;
\n" , std_strings ) ;
 if ( strcmp ( std_strings , "off" ) == 0 ) fprintf ( OPF , "SET escape_string_warning = off;
\n" ) ;
 fprintf ( OPF , "\n" ) ;
 if ( ! data_only ) {
 if ( output_clean ) {
 if ( ! globals_only && ! roles_only && ! tablespaces_only ) dropDBs ( conn ) ;
 if ( ! roles_only && ! no_tablespaces ) {
 if ( server_version >= 80000 ) dropTablespaces ( conn ) ;
 }
 if ( ! tablespaces_only ) dropRoles ( conn ) ;
 }
 if ( ! tablespaces_only ) {
 dumpRoles ( conn ) ;
 if ( server_version >= 80100 ) dumpRoleMembership ( conn ) ;
 else dumpGroups ( conn ) ;
 }
 if ( ! roles_only && ! no_tablespaces ) {
 if ( server_version >= 80000 ) dumpTablespaces ( conn ) ;
 }
 if ( binary_upgrade || ( ! globals_only && ! roles_only && ! tablespaces_only ) ) dumpCreateDB ( conn ) ;
 if ( ! tablespaces_only && ! roles_only ) {
 if ( server_version >= 90000 ) dumpDbRoleConfig ( conn ) ;
 }
 }
 if ( ! globals_only && ! roles_only && ! tablespaces_only ) dumpDatabases ( conn ) ;
 PQfinish ( conn ) ;
 if ( verbose ) dumpTimestamp ( "Completed on" ) ;
 fprintf ( OPF , "--\n-- PostgreSQL database cluster dump complete\n--\n\n" ) ;
 if ( filename ) fclose ( OPF ) ;
 exit_nicely ( 0 ) ;
 }