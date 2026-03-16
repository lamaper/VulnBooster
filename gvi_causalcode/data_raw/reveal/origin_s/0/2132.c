RestoreOptions * NewRestoreOptions ( void ) {
 RestoreOptions * opts ;
 opts = ( RestoreOptions * ) pg_malloc0 ( sizeof ( RestoreOptions ) ) ;
 opts -> format = archUnknown ;
 opts -> promptPassword = TRI_DEFAULT ;
 opts -> dumpSections = DUMP_UNSECTIONED ;
 return opts ;
 }