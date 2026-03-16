teReqs TocIDRequired ( ArchiveHandle * AH , DumpId id ) {
 TocEntry * te = getTocEntryByDumpId ( AH , id ) ;
 if ( ! te ) return 0 ;
 return te -> reqs ;
 }