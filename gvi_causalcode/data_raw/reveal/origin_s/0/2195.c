static void restore_toc_entries_prefork ( ArchiveHandle * AH ) {
 bool skipped_some ;
 TocEntry * next_work_item ;
 ahlog ( AH , 2 , "entering restore_toc_entries_prefork\n" ) ;
 fix_dependencies ( AH ) ;
 skipped_some = false ;
 for ( next_work_item = AH -> toc -> next ;
 next_work_item != AH -> toc ;
 next_work_item = next_work_item -> next ) {
 if ( next_work_item -> section != SECTION_PRE_DATA ) {
 if ( next_work_item -> section == SECTION_DATA || next_work_item -> section == SECTION_POST_DATA ) {
 skipped_some = true ;
 continue ;
 }
 else {
 if ( skipped_some ) continue ;
 }
 }
 ahlog ( AH , 1 , "processing item %d %s %s\n" , next_work_item -> dumpId , next_work_item -> desc , next_work_item -> tag ) ;
 ( void ) restore_toc_entry ( AH , next_work_item , false ) ;
 reduce_dependencies ( AH , next_work_item , NULL ) ;
 }
 DisconnectDatabase ( & AH -> public ) ;
 if ( AH -> currUser ) free ( AH -> currUser ) ;
 AH -> currUser = NULL ;
 if ( AH -> currSchema ) free ( AH -> currSchema ) ;
 AH -> currSchema = NULL ;
 if ( AH -> currTablespace ) free ( AH -> currTablespace ) ;
 AH -> currTablespace = NULL ;
 AH -> currWithOids = - 1 ;
 }