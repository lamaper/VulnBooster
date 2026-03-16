void EndRestoreBlobs ( ArchiveHandle * AH ) {
 RestoreOptions * ropt = AH -> public . ropt ;
 if ( ! ropt -> single_txn ) {
 if ( AH -> connection ) CommitTransaction ( & AH -> public ) ;
 else ahprintf ( AH , "COMMIT;
\n\n" ) ;
 }
 ahlog ( AH , 1 , ngettext ( "restored %d large object\n" , "restored %d large objects\n" , AH -> blobCount ) , AH -> blobCount ) ;
 }