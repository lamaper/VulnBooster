static void processStdStringsEntry ( ArchiveHandle * AH , TocEntry * te ) {
 char * ptr1 ;
 ptr1 = strchr ( te -> defn , '\'' ) ;
 if ( ptr1 && strncmp ( ptr1 , "'on'" , 4 ) == 0 ) AH -> public . std_strings = true ;
 else if ( ptr1 && strncmp ( ptr1 , "'off'" , 5 ) == 0 ) AH -> public . std_strings = false ;
 else exit_horribly ( modulename , "invalid STDSTRINGS item: %s\n" , te -> defn ) ;
 }