void DeCloneArchive ( ArchiveHandle * AH ) {
 Assert ( AH -> connection == NULL ) ;
 ( AH -> DeClonePtr ) ( AH ) ;
 if ( AH -> sqlparse . curCmd ) destroyPQExpBuffer ( AH -> sqlparse . curCmd ) ;
 if ( AH -> currUser ) free ( AH -> currUser ) ;
 if ( AH -> currSchema ) free ( AH -> currSchema ) ;
 if ( AH -> currTablespace ) free ( AH -> currTablespace ) ;
 if ( AH -> savedPassword ) free ( AH -> savedPassword ) ;
 free ( AH ) ;
 }