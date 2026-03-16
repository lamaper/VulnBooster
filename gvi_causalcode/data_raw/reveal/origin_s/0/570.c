void InitDumpOptions ( DumpOptions * opts ) {
 memset ( opts , 0 , sizeof ( DumpOptions ) ) ;
 opts -> include_everything = true ;
 opts -> dumpSections = DUMP_UNSECTIONED ;
 }