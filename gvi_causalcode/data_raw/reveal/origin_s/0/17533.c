static void processEncodingEntry ( ArchiveHandle * AH , TocEntry * te ) {
 char * defn = pg_strdup ( te -> defn ) ;
 char * ptr1 ;
 char * ptr2 = NULL ;
 int encoding ;
 ptr1 = strchr ( defn , '\'' ) ;
 if ( ptr1 ) ptr2 = strchr ( ++ ptr1 , '\'' ) ;
 if ( ptr2 ) {
 * ptr2 = '\0' ;
 encoding = pg_char_to_encoding ( ptr1 ) ;
 if ( encoding < 0 ) exit_horribly ( modulename , "unrecognized encoding \"%s\"\n" , ptr1 ) ;
 AH -> public . encoding = encoding ;
 }
 else exit_horribly ( modulename , "invalid ENCODING item: %s\n" , te -> defn ) ;
 free ( defn ) ;
 }