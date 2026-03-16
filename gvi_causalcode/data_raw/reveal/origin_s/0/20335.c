DumpOptions * NewDumpOptions ( void ) {
 DumpOptions * opts = ( DumpOptions * ) pg_malloc ( sizeof ( DumpOptions ) ) ;
 InitDumpOptions ( opts ) ;
 return opts ;
 }