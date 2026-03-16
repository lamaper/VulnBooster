int EndBlob ( Archive * AHX , Oid oid ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 if ( AH -> EndBlobPtr ) ( * AH -> EndBlobPtr ) ( AH , AH -> currToc , oid ) ;
 return 1 ;
 }