int StartBlob ( Archive * AHX , Oid oid ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 if ( ! AH -> StartBlobPtr ) exit_horribly ( modulename , "large-object output not supported in chosen format\n" ) ;
 ( * AH -> StartBlobPtr ) ( AH , AH -> currToc , oid ) ;
 return 1 ;
 }