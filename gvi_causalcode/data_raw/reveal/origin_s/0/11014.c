static void usage ( int status ) {
 ( void ) fputs ( _ ( "Usage: su [options] [LOGIN]\n" "\n" "Options:\n" " -c, --command COMMAND pass COMMAND to the invoked shell\n" " -h, --help display this help message and exit\n" " -, -l, --login make the shell a login shell\n" " -m, -p,\n" " --preserve-environment do not reset environment variables, and\n" " keep the same shell\n" " -s, --shell SHELL use SHELL instead of the default in passwd\n" "\n" ) , ( E_SUCCESS != status ) ? stderr : stdout ) ;
 exit ( status ) ;
 }