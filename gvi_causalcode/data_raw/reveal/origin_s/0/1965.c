static void dump_lo_buf ( ArchiveHandle * AH ) {
 if ( AH -> connection ) {
 size_t res ;
 res = lo_write ( AH -> connection , AH -> loFd , AH -> lo_buf , AH -> lo_buf_used ) ;
 ahlog ( AH , 5 , ngettext ( "wrote %lu byte of large object data (result = %lu)\n" , "wrote %lu bytes of large object data (result = %lu)\n" , AH -> lo_buf_used ) , ( unsigned long ) AH -> lo_buf_used , ( unsigned long ) res ) ;
 if ( res != AH -> lo_buf_used ) exit_horribly ( modulename , "could not write to large object (result: %lu, expected: %lu)\n" , ( unsigned long ) res , ( unsigned long ) AH -> lo_buf_used ) ;
 }
 else {
 PQExpBuffer buf = createPQExpBuffer ( ) ;
 appendByteaLiteralAHX ( buf , ( const unsigned char * ) AH -> lo_buf , AH -> lo_buf_used , AH ) ;
 AH -> writingBlob = 0 ;
 ahprintf ( AH , "SELECT pg_catalog.lowrite(0, %s);
\n" , buf -> data ) ;
 AH -> writingBlob = 1 ;
 destroyPQExpBuffer ( buf ) ;
 }
 AH -> lo_buf_used = 0 ;
 }