static void repoint_table_dependencies ( ArchiveHandle * AH ) {
 TocEntry * te ;
 int i ;
 DumpId olddep ;
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 if ( te -> section != SECTION_POST_DATA ) continue ;
 for ( i = 0 ;
 i < te -> nDeps ;
 i ++ ) {
 olddep = te -> dependencies [ i ] ;
 if ( olddep <= AH -> maxDumpId && AH -> tableDataId [ olddep ] != 0 ) {
 te -> dependencies [ i ] = AH -> tableDataId [ olddep ] ;
 ahlog ( AH , 2 , "transferring dependency %d -> %d to %d\n" , te -> dumpId , olddep , AH -> tableDataId [ olddep ] ) ;
 }
 }
 }
 }