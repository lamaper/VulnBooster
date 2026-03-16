void ahlog ( ArchiveHandle * AH , int level , const char * fmt , ... ) {
 va_list ap ;
 if ( AH -> debugLevel < level && ( ! AH -> public . verbose || level > 1 ) ) return ;
 va_start ( ap , fmt ) ;
 vwrite_msg ( NULL , fmt , ap ) ;
 va_end ( ap ) ;
 }