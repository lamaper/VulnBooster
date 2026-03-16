static void inhibit_data_for_failed_table ( ArchiveHandle * AH , TocEntry * te ) {
 ahlog ( AH , 1 , "table \"%s\" could not be created, will not restore its data\n" , te -> tag ) ;
 if ( AH -> tableDataId [ te -> dumpId ] != 0 ) {
 TocEntry * ted = AH -> tocsByDumpId [ AH -> tableDataId [ te -> dumpId ] ] ;
 ted -> reqs = 0 ;
 }
 }