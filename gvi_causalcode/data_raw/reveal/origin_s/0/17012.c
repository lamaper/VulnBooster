static void usage ( ) {
 fprintf ( stderr , _ ( "Usage: %s [-r realm] [-p principal] [-q query] " "[clnt|local args]\n" "\tclnt args: [-s admin_server[:port]] " "[[-c ccache]|[-k [-t keytab]]]|[-n]\n" "\tlocal args: [-x db_args]* [-d dbname] " "[-e \"enc:salt ...\"] [-m]\n" "where,\n\t[-x db_args]* - any number of database specific " "arguments.\n" "\t\t\tLook at each database documentation for supported " "arguments\n" ) , whoami ) ;
 exit ( 1 ) ;
 }