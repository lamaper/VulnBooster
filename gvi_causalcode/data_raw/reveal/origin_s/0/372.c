static int qemuMonitorParseBalloonInfo ( char * text , virDomainMemoryStatPtr stats , unsigned int nr_stats ) {
 char * p = text ;
 unsigned int nr_stats_found = 0 ;
 if ( parseMemoryStat ( & p , VIR_DOMAIN_MEMORY_STAT_ACTUAL_BALLOON , "actual=" , & stats [ nr_stats_found ] ) == 1 ) {
 nr_stats_found ++ ;
 }
 while ( * p && nr_stats_found < nr_stats ) {
 if ( parseMemoryStat ( & p , VIR_DOMAIN_MEMORY_STAT_SWAP_IN , ",mem_swapped_in=" , & stats [ nr_stats_found ] ) || parseMemoryStat ( & p , VIR_DOMAIN_MEMORY_STAT_SWAP_OUT , ",mem_swapped_out=" , & stats [ nr_stats_found ] ) || parseMemoryStat ( & p , VIR_DOMAIN_MEMORY_STAT_MAJOR_FAULT , ",major_page_faults=" , & stats [ nr_stats_found ] ) || parseMemoryStat ( & p , VIR_DOMAIN_MEMORY_STAT_MINOR_FAULT , ",minor_page_faults=" , & stats [ nr_stats_found ] ) || parseMemoryStat ( & p , VIR_DOMAIN_MEMORY_STAT_UNUSED , ",free_mem=" , & stats [ nr_stats_found ] ) || parseMemoryStat ( & p , VIR_DOMAIN_MEMORY_STAT_AVAILABLE , ",total_mem=" , & stats [ nr_stats_found ] ) ) nr_stats_found ++ ;
 if ( * p == ',' ) p ++ ;
 p = strchr ( p , ',' ) ;
 if ( ! p ) break ;
 }
 return nr_stats_found ;
 }