static void kadmin_addmodpol_usage ( char * func ) {
 fprintf ( stderr , _ ( "usage;
 %s [options] policy\n" ) , func ) ;
 fprintf ( stderr , _ ( "\toptions are:\n" ) ) ;
 fprintf ( stderr , _ ( "\t\t[-maxlife time] [-minlife time] [-minlength length]\n" "\t\t[-minclasses number] [-history number]\n" "\t\t[-maxfailure number] [-failurecountinterval time]\n" "\t\t[-allowedkeysalts keysalts]\n" ) ) ;
 fprintf ( stderr , _ ( "\t\t[-lockoutduration time]\n" ) ) ;
 }