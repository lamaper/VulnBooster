static void SetOutput ( ArchiveHandle * AH , const char * filename , int compression ) {
 int fn ;
 if ( filename ) fn = - 1 ;
 else if ( AH -> FH ) fn = fileno ( AH -> FH ) ;
 else if ( AH -> fSpec ) {
 fn = - 1 ;
 filename = AH -> fSpec ;
 }
 else fn = fileno ( stdout ) ;

 char fmode [ 10 ] ;
 sprintf ( fmode , "wb%d" , compression ) ;
 if ( fn >= 0 ) AH -> OF = gzdopen ( dup ( fn ) , fmode ) ;
 else AH -> OF = gzopen ( filename , fmode ) ;
 AH -> gzOut = 1 ;
 }
 else # endif {
 if ( AH -> mode == archModeAppend ) {
 if ( fn >= 0 ) AH -> OF = fdopen ( dup ( fn ) , PG_BINARY_A ) ;
 else AH -> OF = fopen ( filename , PG_BINARY_A ) ;
 }
 else {
 if ( fn >= 0 ) AH -> OF = fdopen ( dup ( fn ) , PG_BINARY_W ) ;
 else AH -> OF = fopen ( filename , PG_BINARY_W ) ;
 }
 AH -> gzOut = 0 ;
 }
 if ( ! AH -> OF ) {
 if ( filename ) exit_horribly ( modulename , "could not open output file \"%s\": %s\n" , filename , strerror ( errno ) ) ;
 else exit_horribly ( modulename , "could not open output file: %s\n" , strerror ( errno ) ) ;
 }
 }