void CloseArchive ( Archive * AHX ) {
 int res = 0 ;
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 ( * AH -> ClosePtr ) ( AH ) ;
 if ( AH -> gzOut ) res = GZCLOSE ( AH -> OF ) ;
 else if ( AH -> OF != stdout ) res = fclose ( AH -> OF ) ;
 if ( res != 0 ) exit_horribly ( modulename , "could not close output file: %s\n" , strerror ( errno ) ) ;
 }