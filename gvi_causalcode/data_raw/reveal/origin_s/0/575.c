static void buildTocEntryArrays ( ArchiveHandle * AH ) {
 DumpId maxDumpId = AH -> maxDumpId ;
 TocEntry * te ;
 AH -> tocsByDumpId = ( TocEntry * * ) pg_malloc0 ( ( maxDumpId + 1 ) * sizeof ( TocEntry * ) ) ;
 AH -> tableDataId = ( DumpId * ) pg_malloc0 ( ( maxDumpId + 1 ) * sizeof ( DumpId ) ) ;
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 if ( te -> dumpId <= 0 || te -> dumpId > maxDumpId ) exit_horribly ( modulename , "bad dumpId\n" ) ;
 AH -> tocsByDumpId [ te -> dumpId ] = te ;
 if ( strcmp ( te -> desc , "TABLE DATA" ) == 0 && te -> nDeps > 0 ) {
 DumpId tableId = te -> dependencies [ 0 ] ;
 if ( tableId <= 0 || tableId > maxDumpId ) exit_horribly ( modulename , "bad table dumpId for TABLE DATA item\n" ) ;
 AH -> tableDataId [ tableId ] = te -> dumpId ;
 }
 }
 }