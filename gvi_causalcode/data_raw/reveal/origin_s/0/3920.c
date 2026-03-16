static void restore_toc_entries_postfork ( ArchiveHandle * AH , TocEntry * pending_list ) {
 RestoreOptions * ropt = AH -> public . ropt ;
 TocEntry * te ;
 ahlog ( AH , 2 , "entering restore_toc_entries_postfork\n" ) ;
 ConnectDatabase ( ( Archive * ) AH , ropt -> dbname , ropt -> pghost , ropt -> pgport , ropt -> username , ropt -> promptPassword ) ;
 _doSetFixedOutputState ( AH ) ;
 for ( te = pending_list -> par_next ;
 te != pending_list ;
 te = te -> par_next ) {
 ahlog ( AH , 1 , "processing missed item %d %s %s\n" , te -> dumpId , te -> desc , te -> tag ) ;
 ( void ) restore_toc_entry ( AH , te , false ) ;
 }
 }