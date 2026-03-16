static void RestoreOutput ( ArchiveHandle * AH , OutputContext savedContext ) {
 int res ;
 if ( AH -> gzOut ) res = GZCLOSE ( AH -> OF ) ;
 else res = fclose ( AH -> OF ) ;
 if ( res != 0 ) exit_horribly ( modulename , "could not close output file: %s\n" , strerror ( errno ) ) ;
 AH -> gzOut = savedContext . gzOut ;
 AH -> OF = savedContext . OF ;
 }