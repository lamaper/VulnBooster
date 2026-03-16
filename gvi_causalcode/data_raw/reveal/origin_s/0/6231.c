void WriteDataChunksForTocEntry ( ArchiveHandle * AH , TocEntry * te ) {
 StartDataPtr startPtr ;
 EndDataPtr endPtr ;
 AH -> currToc = te ;
 if ( strcmp ( te -> desc , "BLOBS" ) == 0 ) {
 startPtr = AH -> StartBlobsPtr ;
 endPtr = AH -> EndBlobsPtr ;
 }
 else {
 startPtr = AH -> StartDataPtr ;
 endPtr = AH -> EndDataPtr ;
 }
 if ( startPtr != NULL ) ( * startPtr ) ( AH , te ) ;
 ( * te -> dataDumper ) ( ( Archive * ) AH , te -> dataDumperArg ) ;
 if ( endPtr != NULL ) ( * endPtr ) ( AH , te ) ;
 AH -> currToc = NULL ;
 }