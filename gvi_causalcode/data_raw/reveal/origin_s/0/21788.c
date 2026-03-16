static TocEntry * get_next_work_item ( ArchiveHandle * AH , TocEntry * ready_list , ParallelState * pstate ) {
 bool pref_non_data = false ;
 TocEntry * data_te = NULL ;
 TocEntry * te ;
 int i , k ;
 if ( pref_non_data ) {
 int count = 0 ;
 for ( k = 0 ;
 k < pstate -> numWorkers ;
 k ++ ) if ( pstate -> parallelSlot [ k ] . args -> te != NULL && pstate -> parallelSlot [ k ] . args -> te -> section == SECTION_DATA ) count ++ ;
 if ( pstate -> numWorkers == 0 || count * 4 < pstate -> numWorkers ) pref_non_data = false ;
 }
 for ( te = ready_list -> par_next ;
 te != ready_list ;
 te = te -> par_next ) {
 bool conflicts = false ;
 for ( i = 0 ;
 i < pstate -> numWorkers && ! conflicts ;
 i ++ ) {
 TocEntry * running_te ;
 if ( pstate -> parallelSlot [ i ] . workerStatus != WRKR_WORKING ) continue ;
 running_te = pstate -> parallelSlot [ i ] . args -> te ;
 if ( has_lock_conflicts ( te , running_te ) || has_lock_conflicts ( running_te , te ) ) {
 conflicts = true ;
 break ;
 }
 }
 if ( conflicts ) continue ;
 if ( pref_non_data && te -> section == SECTION_DATA ) {
 if ( data_te == NULL ) data_te = te ;
 continue ;
 }
 return te ;
 }
 if ( data_te != NULL ) return data_te ;
 ahlog ( AH , 2 , "no item ready\n" ) ;
 return NULL ;
 }