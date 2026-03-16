int qemuMonitorJSONGetMemoryStats ( qemuMonitorPtr mon , virDomainMemoryStatPtr stats , unsigned int nr_stats ) {
 int ret ;
 int got = 0 ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "query-balloon" , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) {
 if ( qemuMonitorJSONHasError ( reply , "DeviceNotActive" ) || qemuMonitorJSONHasError ( reply , "KVMMissingCap" ) ) goto cleanup ;
 ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 if ( ret == 0 ) {
 virJSONValuePtr data ;
 unsigned long long mem ;
 if ( ! ( data = virJSONValueObjectGet ( reply , "return" ) ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "info balloon reply was missing return data" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 if ( virJSONValueObjectHasKey ( data , "actual" ) && ( got < nr_stats ) ) {
 if ( virJSONValueObjectGetNumberUlong ( data , "actual" , & mem ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "info balloon reply was missing balloon actual" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 stats [ got ] . tag = VIR_DOMAIN_MEMORY_STAT_ACTUAL_BALLOON ;
 stats [ got ] . val = ( mem / 1024 ) ;
 got ++ ;
 }
 if ( virJSONValueObjectHasKey ( data , "mem_swapped_in" ) && ( got < nr_stats ) ) {
 if ( virJSONValueObjectGetNumberUlong ( data , "mem_swapped_in" , & mem ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "info balloon reply was missing balloon mem_swapped_in" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 stats [ got ] . tag = VIR_DOMAIN_MEMORY_STAT_SWAP_IN ;
 stats [ got ] . val = ( mem / 1024 ) ;
 got ++ ;
 }
 if ( virJSONValueObjectHasKey ( data , "mem_swapped_out" ) && ( got < nr_stats ) ) {
 if ( virJSONValueObjectGetNumberUlong ( data , "mem_swapped_out" , & mem ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "info balloon reply was missing balloon mem_swapped_out" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 stats [ got ] . tag = VIR_DOMAIN_MEMORY_STAT_SWAP_OUT ;
 stats [ got ] . val = ( mem / 1024 ) ;
 got ++ ;
 }
 if ( virJSONValueObjectHasKey ( data , "major_page_faults" ) && ( got < nr_stats ) ) {
 if ( virJSONValueObjectGetNumberUlong ( data , "major_page_faults" , & mem ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "info balloon reply was missing balloon major_page_faults" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 stats [ got ] . tag = VIR_DOMAIN_MEMORY_STAT_MAJOR_FAULT ;
 stats [ got ] . val = mem ;
 got ++ ;
 }
 if ( virJSONValueObjectHasKey ( data , "minor_page_faults" ) && ( got < nr_stats ) ) {
 if ( virJSONValueObjectGetNumberUlong ( data , "minor_page_faults" , & mem ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "info balloon reply was missing balloon minor_page_faults" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 stats [ got ] . tag = VIR_DOMAIN_MEMORY_STAT_MINOR_FAULT ;
 stats [ got ] . val = mem ;
 got ++ ;
 }
 if ( virJSONValueObjectHasKey ( data , "free_mem" ) && ( got < nr_stats ) ) {
 if ( virJSONValueObjectGetNumberUlong ( data , "free_mem" , & mem ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "info balloon reply was missing balloon free_mem" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 stats [ got ] . tag = VIR_DOMAIN_MEMORY_STAT_UNUSED ;
 stats [ got ] . val = ( mem / 1024 ) ;
 got ++ ;
 }
 if ( virJSONValueObjectHasKey ( data , "total_mem" ) && ( got < nr_stats ) ) {
 if ( virJSONValueObjectGetNumberUlong ( data , "total_mem" , & mem ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "info balloon reply was missing balloon total_mem" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 stats [ got ] . tag = VIR_DOMAIN_MEMORY_STAT_AVAILABLE ;
 stats [ got ] . val = ( mem / 1024 ) ;
 got ++ ;
 }
 }
 }
 if ( got > 0 ) ret = got ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }