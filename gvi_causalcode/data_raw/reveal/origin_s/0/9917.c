static int qemuAgentSetVCPUsCommand ( qemuAgentPtr mon , qemuAgentCPUInfoPtr info , size_t ninfo , int * nmodified ) {
 int ret = - 1 ;
 virJSONValuePtr cmd = NULL ;
 virJSONValuePtr reply = NULL ;
 virJSONValuePtr cpus = NULL ;
 virJSONValuePtr cpu = NULL ;
 size_t i ;
 * nmodified = 0 ;
 if ( ! ( cpus = virJSONValueNewArray ( ) ) ) goto cleanup ;
 for ( i = 0 ;
 i < ninfo ;
 i ++ ) {
 qemuAgentCPUInfoPtr in = & info [ i ] ;
 if ( ! in -> modified ) continue ;
 ( * nmodified ) ++ ;
 if ( ! ( cpu = virJSONValueNewObject ( ) ) ) goto cleanup ;
 if ( virJSONValueObjectAppendNumberInt ( cpu , "logical-id" , in -> id ) < 0 ) goto cleanup ;
 if ( virJSONValueObjectAppendBoolean ( cpu , "online" , in -> online ) < 0 ) goto cleanup ;
 if ( virJSONValueArrayAppend ( cpus , cpu ) < 0 ) goto cleanup ;
 cpu = NULL ;
 }
 if ( * nmodified == 0 ) {
 ret = 0 ;
 goto cleanup ;
 }
 if ( ! ( cmd = qemuAgentMakeCommand ( "guest-set-vcpus" , "a:vcpus" , cpus , NULL ) ) ) goto cleanup ;
 cpus = NULL ;
 if ( qemuAgentCommand ( mon , cmd , & reply , true , VIR_DOMAIN_QEMU_AGENT_COMMAND_BLOCK ) < 0 ) goto cleanup ;
 if ( qemuAgentCheckError ( cmd , reply ) < 0 ) goto cleanup ;
 if ( virJSONValueObjectGetNumberInt ( reply , "return" , & ret ) < 0 || ret <= 0 || ret > * nmodified ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "guest agent returned malformed or invalid return value" ) ) ;
 ret = - 1 ;
 }
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 virJSONValueFree ( cpu ) ;
 virJSONValueFree ( cpus ) ;
 return ret ;
 }