void CommitTransaction ( Archive * AHX ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 ExecuteSqlCommand ( AH , "COMMIT" , "could not commit database transaction" ) ;
 }