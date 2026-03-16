void ProcessArchiveRestoreOptions ( Archive * AHX ) {
 ArchiveHandle * AH = ( ArchiveHandle * ) AHX ;
 RestoreOptions * ropt = AH -> public . ropt ;
 TocEntry * te ;
 teSection curSection ;
 curSection = SECTION_PRE_DATA ;
 for ( te = AH -> toc -> next ;
 te != AH -> toc ;
 te = te -> next ) {
 if ( AH -> mode != archModeRead ) {
 switch ( te -> section ) {
 case SECTION_NONE : break ;
 case SECTION_PRE_DATA : if ( curSection != SECTION_PRE_DATA ) write_msg ( modulename , "WARNING: archive items not in correct section order\n" ) ;
 break ;
 case SECTION_DATA : if ( curSection == SECTION_POST_DATA ) write_msg ( modulename , "WARNING: archive items not in correct section order\n" ) ;
 break ;
 case SECTION_POST_DATA : break ;
 default : exit_horribly ( modulename , "unexpected section code %d\n" , ( int ) te -> section ) ;
 break ;
 }
 }
 if ( te -> section != SECTION_NONE ) curSection = te -> section ;
 te -> reqs = _tocEntryRequired ( te , curSection , ropt ) ;
 }
 if ( ropt -> strict_names ) StrictNamesCheck ( ropt ) ;
 }