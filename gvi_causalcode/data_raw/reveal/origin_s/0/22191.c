static void mark_create_done ( ArchiveHandle * AH , TocEntry * te ) {
 if ( AH -> tableDataId [ te -> dumpId ] != 0 ) {
 TocEntry * ted = AH -> tocsByDumpId [ AH -> tableDataId [ te -> dumpId ] ] ;
 ted -> created = true ;
 }
 }