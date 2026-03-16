static void qemuMonitorJSONHandleBlockJob ( qemuMonitorPtr mon , virJSONValuePtr data ) {
 const char * device ;
 const char * type_str ;
 int type = VIR_DOMAIN_BLOCK_JOB_TYPE_UNKNOWN ;
 unsigned long long offset , len ;
 int status = VIR_DOMAIN_BLOCK_JOB_FAILED ;
 if ( ( device = virJSONValueObjectGetString ( data , "device" ) ) == NULL ) {
 VIR_WARN ( "missing device in block job event" ) ;
 goto out ;
 }
 if ( virJSONValueObjectGetNumberUlong ( data , "offset" , & offset ) < 0 ) {
 VIR_WARN ( "missing offset in block job event" ) ;
 goto out ;
 }
 if ( virJSONValueObjectGetNumberUlong ( data , "len" , & len ) < 0 ) {
 VIR_WARN ( "missing len in block job event" ) ;
 goto out ;
 }
 if ( ( type_str = virJSONValueObjectGetString ( data , "type" ) ) == NULL ) {
 VIR_WARN ( "missing type in block job event" ) ;
 goto out ;
 }
 if ( STREQ ( type_str , "stream" ) ) type = VIR_DOMAIN_BLOCK_JOB_TYPE_PULL ;
 if ( offset != 0 && offset == len ) status = VIR_DOMAIN_BLOCK_JOB_COMPLETED ;
 out : qemuMonitorEmitBlockJob ( mon , device , type , status ) ;
 }