static int parseMemoryStat ( char * * text , unsigned int tag , const char * search , virDomainMemoryStatPtr stat ) {
 char * dummy ;
 unsigned long long value ;
 if ( STRPREFIX ( * text , search ) ) {
 * text += strlen ( search ) ;
 if ( virStrToLong_ull ( * text , & dummy , 10 , & value ) ) {
 VIR_DEBUG ( "error reading %s: %s" , search , * text ) ;
 return 0 ;
 }
 switch ( tag ) {
 case VIR_DOMAIN_MEMORY_STAT_ACTUAL_BALLOON : value <<= 10 ;
 break ;
 case VIR_DOMAIN_MEMORY_STAT_SWAP_IN : case VIR_DOMAIN_MEMORY_STAT_SWAP_OUT : case VIR_DOMAIN_MEMORY_STAT_UNUSED : case VIR_DOMAIN_MEMORY_STAT_AVAILABLE : value >>= 10 ;
 }
 stat -> tag = tag ;
 stat -> val = value ;
 return 1 ;
 }
 return 0 ;
 }