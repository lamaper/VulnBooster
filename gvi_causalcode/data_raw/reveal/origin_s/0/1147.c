static void reduce_dependencies ( ArchiveHandle * AH , TocEntry * te , TocEntry * ready_list ) {
 int i ;
 ahlog ( AH , 2 , "reducing dependencies for %d\n" , te -> dumpId ) ;
 for ( i = 0 ;
 i < te -> nRevDeps ;
 i ++ ) {
 TocEntry * otherte = AH -> tocsByDumpId [ te -> revDeps [ i ] ] ;
 otherte -> depCount -- ;
 if ( otherte -> depCount == 0 && otherte -> par_prev != NULL ) {
 par_list_remove ( otherte ) ;
 par_list_append ( ready_list , otherte ) ;
 }
 }
 }