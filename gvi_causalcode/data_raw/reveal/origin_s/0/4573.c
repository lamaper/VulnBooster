void warn_or_exit_horribly ( ArchiveHandle * AH , const char * modulename , const char * fmt , ... ) {
 va_list ap ;
 switch ( AH -> stage ) {
 case STAGE_NONE : break ;
 case STAGE_INITIALIZING : if ( AH -> stage != AH -> lastErrorStage ) write_msg ( modulename , "Error while INITIALIZING:\n" ) ;
 break ;
 case STAGE_PROCESSING : if ( AH -> stage != AH -> lastErrorStage ) write_msg ( modulename , "Error while PROCESSING TOC:\n" ) ;
 break ;
 case STAGE_FINALIZING : if ( AH -> stage != AH -> lastErrorStage ) write_msg ( modulename , "Error while FINALIZING:\n" ) ;
 break ;
 }
 if ( AH -> currentTE != NULL && AH -> currentTE != AH -> lastErrorTE ) {
 write_msg ( modulename , "Error from TOC entry %d;
 %u %u %s %s %s\n" , AH -> currentTE -> dumpId , AH -> currentTE -> catalogId . tableoid , AH -> currentTE -> catalogId . oid , AH -> currentTE -> desc , AH -> currentTE -> tag , AH -> currentTE -> owner ) ;
 }
 AH -> lastErrorStage = AH -> stage ;
 AH -> lastErrorTE = AH -> currentTE ;
 va_start ( ap , fmt ) ;
 vwrite_msg ( modulename , fmt , ap ) ;
 va_end ( ap ) ;
 if ( AH -> public . exit_on_error ) exit_nicely ( 1 ) ;
 else AH -> public . n_errors ++ ;
 }