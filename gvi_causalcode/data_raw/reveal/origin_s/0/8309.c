static int qemuMonitorJSONGetBlockJobInfoOne ( virJSONValuePtr entry , const char * device , virDomainBlockJobInfoPtr info ) {
 const char * this_dev ;
 const char * type ;
 unsigned long long speed_bytes ;
 if ( ( this_dev = virJSONValueObjectGetString ( entry , "device" ) ) == NULL ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "entry was missing 'device'" ) ) ;
 return - 1 ;
 }
 if ( ! STREQ ( this_dev , device ) ) return - 1 ;
 type = virJSONValueObjectGetString ( entry , "type" ) ;
 if ( ! type ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "entry was missing 'type'" ) ) ;
 return - 1 ;
 }
 if ( STREQ ( type , "stream" ) ) info -> type = VIR_DOMAIN_BLOCK_JOB_TYPE_PULL ;
 else info -> type = VIR_DOMAIN_BLOCK_JOB_TYPE_UNKNOWN ;
 if ( virJSONValueObjectGetNumberUlong ( entry , "speed" , & speed_bytes ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "entry was missing 'speed'" ) ) ;
 return - 1 ;
 }
 info -> bandwidth = speed_bytes / 1024ULL / 1024ULL ;
 if ( virJSONValueObjectGetNumberUlong ( entry , "offset" , & info -> cur ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "entry was missing 'offset'" ) ) ;
 return - 1 ;
 }
 if ( virJSONValueObjectGetNumberUlong ( entry , "len" , & info -> end ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "entry was missing 'len'" ) ) ;
 return - 1 ;
 }
 return 0 ;
 }