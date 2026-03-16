void EndRestoreBlob ( ArchiveHandle * AH , Oid oid ) {
 if ( AH -> lo_buf_used > 0 ) {
 dump_lo_buf ( AH ) ;
 }
 AH -> writingBlob = 0 ;
 if ( AH -> connection ) {
 lo_close ( AH -> connection , AH -> loFd ) ;
 AH -> loFd = - 1 ;
 }
 else {
 ahprintf ( AH , "SELECT pg_catalog.lo_close(0);
\n\n" ) ;
 }
 }