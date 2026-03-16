static void _reconnectToDB ( ArchiveHandle * AH , const char * dbname ) {
 if ( RestoringToDB ( AH ) ) ReconnectToServer ( AH , dbname , NULL ) ;
 else {
 if ( dbname ) {
 PQExpBufferData connectbuf ;
 initPQExpBuffer ( & connectbuf ) ;
 appendPsqlMetaConnect ( & connectbuf , dbname ) ;
 ahprintf ( AH , "%s\n" , connectbuf . data ) ;
 termPQExpBuffer ( & connectbuf ) ;
 }
 else ahprintf ( AH , "%s\n" , "\\connect -\n" ) ;
 }
 if ( AH -> currUser ) free ( AH -> currUser ) ;
 AH -> currUser = NULL ;
 if ( AH -> currSchema ) free ( AH -> currSchema ) ;
 AH -> currSchema = NULL ;
 if ( AH -> currTablespace ) free ( AH -> currTablespace ) ;
 AH -> currTablespace = NULL ;
 AH -> currWithOids = - 1 ;
 _doSetFixedOutputState ( AH ) ;
 }