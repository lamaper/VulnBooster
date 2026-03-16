void proto_register_pcp ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_pcp_pdu_length , {
 "PDU Length" , "pcp.length" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pdu_type , {
 "Type" , "pcp.type" , FT_UINT32 , BASE_HEX , VALS ( packettypenames ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pdu_pid , {
 "From" , "pcp.from" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pdu_error , {
 "Error" , "pcp.error" , FT_INT32 , BASE_DEC , VALS ( packettypenames_errors ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pdu_padding , {
 "Padding" , "pcp.padding" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_creds_number_of , {
 "Number of Credentials" , "pcp.creds.number" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_creds_type , {
 "Credentials Type" , "pcp.creds.type" , FT_UINT8 , BASE_DEC , VALS ( packettypenames_creds ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_creds_version , {
 "Credentials Version" , "pcp.creds.version" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_start , {
 "Start" , "pcp.start" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_start_zero , {
 "Start Bit" , "pcp.start.zero" , FT_BOOLEAN , 8 , TFS ( & tfs_set_notset ) , 0x80 , NULL , HFILL }
 }
 , {
 & hf_pcp_start_version , {
 "Version" , "pcp.start.version" , FT_UINT8 , BASE_DEC , NULL , 0x7F , NULL , HFILL }
 }
 , {
 & hf_pcp_start_status , {
 "Start Status" , "pcp.start.status" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_start_licensed , {
 "Licensed" , "pcp.start.licensed" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_features_flags , {
 "Features" , "pcp.features.flags" , FT_UINT16 , BASE_HEX , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_features_flags_secure , {
 "Secure" , "pcp.features.flags.secure" , FT_BOOLEAN , 16 , TFS ( & tfs_set_notset ) , PCP_PDU_FLAG_SECURE , NULL , HFILL }
 }
 , {
 & hf_pcp_features_flags_compress , {
 "Compression" , "pcp.features.flags.compression" , FT_BOOLEAN , 16 , TFS ( & tfs_set_notset ) , PCP_PDU_FLAG_COMPRESS , NULL , HFILL }
 }
 , {
 & hf_pcp_features_flags_auth , {
 "Authentication" , "pcp.features.flags.auth" , FT_BOOLEAN , 16 , TFS ( & tfs_set_notset ) , PCP_PDU_FLAG_AUTH , NULL , HFILL }
 }
 , {
 & hf_pcp_features_flags_creds_reqd , {
 "Credentials Required" , "pcp.features.flags.creds_reqd" , FT_BOOLEAN , 16 , TFS ( & tfs_set_notset ) , PCP_PDU_FLAG_CREDS_REQD , NULL , HFILL }
 }
 , {
 & hf_pcp_features_flags_secure_ack , {
 "Secure Acknowledgement" , "pcp.features.flags.secure_ack" , FT_BOOLEAN , 16 , TFS ( & tfs_set_notset ) , PCP_PDU_FLAG_SECURE_ACK , NULL , HFILL }
 }
 , {
 & hf_pcp_features_flags_no_nss_init , {
 "No NSS Init" , "pcp.features.flags.no_nss_init" , FT_BOOLEAN , 16 , TFS ( & tfs_set_notset ) , PCP_PDU_FLAG_NO_NSS_INIT , NULL , HFILL }
 }
 , {
 & hf_pcp_features_flags_container , {
 "Container" , "pcp.features.flags.container" , FT_BOOLEAN , 16 , TFS ( & tfs_set_notset ) , PCP_PDU_FLAG_CONTAINER , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_traverse , {
 "PMNS Traverse" , "pcp.pmns_traverse" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_subtype , {
 "Subtype" , "pcp.pmns.subtype" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_namelen , {
 "Name Length" , "pcp.pmns.namelen" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_name , {
 "Name" , "pcp.pmns.name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_names , {
 "PMNS Names" , "pcp.pmns_names" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_names_nstrbytes , {
 "String Bytes" , "pcp.pmns_names.nstrbytes" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_names_numstatus , {
 "Status" , "pcp.pmns_names.numstatus" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_names_numnames , {
 "Number of Names" , "pcp.pmns_names.numnames" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_names_nametree , {
 "Names" , "pcp.pmns_names.nametree" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_names_nametree_status , {
 "Status" , "pcp.pmns_names.nametree.status" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_names_nametree_namelen , {
 "Length" , "pcp.pmns_names.nametree.namelen" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_names_nametree_name , {
 "Name" , "pcp.pmns_names.nametree.name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_ids , {
 "PMNS IDs" , "pcp.pmns_ids" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_ids_status , {
 "Status" , "pcp.pmns_ids.status" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_ids_numids , {
 "Number of IDs" , "pcp.pmns_ids.numids" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmns_child , {
 "PMID Child" , "pcp.pmns.child" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmid , {
 "PMID" , "pcp.pmid" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmid_flag , {
 "Flag" , "pcp.pmid.flag" , FT_BOOLEAN , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmid_domain , {
 "Domain" , "pcp.pmid.domain" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmid_cluster , {
 "Cluster" , "pcp.pmid.cluster" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmid_item , {
 "Item" , "pcp.pmid.item" , FT_UINT16 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmid_type , {
 "Type" , "pcp.pmid.type" , FT_INT8 , BASE_DEC , VALS ( packettypenames_pm_types ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmid_sem , {
 "Type Semantics" , "pcp.pmid.sem" , FT_UINT32 , BASE_DEC , VALS ( packettypenames_pm_types_sem ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_pmid_inst , {
 "Instance" , "pcp.pmid.inst" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_profile , {
 "Profile" , "pcp.profile" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_ctxnum , {
 "Context Number" , "pcp.ctxnum" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_profile_g_state , {
 "Global Include/Exclude State" , "pcp.profile.g_state" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_profile_numprof , {
 "Number of Profiles" , "pcp.profile.numprof" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_profile_profile , {
 "Each Profile" , "pcp.profile.profile" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_profile_profile_state , {
 "Include/Exclude State" , "pcp.profile.profile.state" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_profile_profile_numinst , {
 "Number Instances to Follow" , "pcp.profile.profile.numinst" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_fetch , {
 "Fetch" , "pcp.fetch" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_fetch_numpmid , {
 "Number PMIDs" , "pcp.fetch.numpmid" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_when , {
 "Time Value" , "pcp.when" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_when_sec , {
 "Seconds" , "pcp.when.sec" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_when_usec , {
 "Microseconds" , "pcp.when.usec" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_desc_req , {
 "Description Request" , "pcp.desc_req" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_desc , {
 "Description Response" , "pcp.desc" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_units , {
 "PMID Units" , "pcp.units" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_units_dimspace , {
 "Dimension Space" , "pcp.units.dimspace" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_units_dimtime , {
 "Dimension Time" , "pcp.units.dimtime" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_units_dimcount , {
 "Dimension Count" , "pcp.units.dimcount" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_units_scalespace , {
 "Scale Space" , "pcp.units.scalespace" , FT_UINT8 , BASE_DEC , VALS ( packettypenames_pm_units_space ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_units_scaletime , {
 "Scale Time" , "pcp.units.scalespace" , FT_UINT8 , BASE_DEC , VALS ( packettypenames_pm_units_time ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_units_scalecount , {
 "Scale Count" , "pcp.units.scalecount" , FT_UINT8 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_req , {
 "Instance Request" , "pcp.instance_req" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instances , {
 "Instance Response" , "pcp.instances" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instances_numinst , {
 "Number of Instances" , "pcp.instance_resp.numinst" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance , {
 "Instance" , "pcp.instance" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_namelen , {
 "Name Length" , "pcp.instance.namelen" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_name , {
 "Name" , "pcp.instance.name" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_indom , {
 "Instance Domain" , "pcp.instance.indom" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_valoffset , {
 "Instance Offset" , "pcp.instance.valoffset" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_vallength , {
 "Instance Value Length" , "pcp.instance.vallength" , FT_INT24 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_value_insitu , {
 "Instance Value" , "pcp.instance.value.uint" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_value_ptr , {
 "Instance Value" , "pcp.instance.value.string" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_value_int , {
 "Instance Value" , "pcp.instance.value.int" , FT_INT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_value_uint , {
 "Instance Value" , "pcp.instance.value.uint" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_value_int64 , {
 "Instance Value" , "pcp.instance.value.int64" , FT_INT64 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_value_uint64 , {
 "Instance Value" , "pcp.instance.value.uint64" , FT_UINT64 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_value_float , {
 "Instance Value" , "pcp.instance.value.float" , FT_FLOAT , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_value_double , {
 "Instance Value" , "pcp.instance.value.float" , FT_DOUBLE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_instance_value_aggr , {
 "Instance Value" , "pcp.instance.value.bytes" , FT_BYTES , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_results , {
 "Fetch Results" , "pcp.results" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_results_numpmid , {
 "Number of PMIDs" , "pcp.results.numpmid" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_result , {
 "Result" , "pcp.result" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_result_numval , {
 "Number of Values" , "pcp.result.numval" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_result_valfmt , {
 "Value Encoding Format" , "pcp.result.valfmt" , FT_UINT32 , BASE_DEC , VALS ( packettypenames_valfmt ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_text_req , {
 "Text Request" , "pcp.text_req" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_text_type , {
 "Help Text Type" , "pcp.text.type" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_text_type_format , {
 "Text Type Format" , "pcp.text.type.format" , FT_UINT8 , BASE_DEC , VALS ( packettypenames_text_type_format ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_text_type_ident , {
 "Text Type Ident" , "pcp.text.type.ident" , FT_UINT8 , BASE_DEC , VALS ( packettypenames_text_type_ident ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_text , {
 "Text Response" , "pcp.text" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_text_ident , {
 "Text Ident (raw)" , "pcp.text.ident" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_text_buflen , {
 "Text Buffer Length" , "pcp.text.buflen" , FT_UINT32 , BASE_DEC , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_text_buffer , {
 "Text Buffer" , "pcp.text.buffer" , FT_STRING , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , {
 & hf_pcp_user_auth_payload , {
 "User Authentication Payload" , "pcp.user_auth_payload" , FT_NONE , BASE_NONE , NULL , 0x0 , NULL , HFILL }
 }
 , }
 ;
 static gint * ett [ ] = {
 & ett_pcp , & ett_pcp_pdu_length , & ett_pcp_pdu_type , & ett_pcp_pdu_pid , & ett_pcp_pdu_error , & ett_pcp_pdu_padding , & ett_pcp_creds_number_of , & ett_pcp_creds_type , & ett_pcp_creds_vala , & ett_pcp_creds_valb , & ett_pcp_creds_valc , & ett_pcp_start , & ett_pcp_start_status , & ett_pcp_start_zero , & ett_pcp_start_version , & ett_pcp_start_licensed , & ett_pcp_start_features , & ett_pcp_pmns_traverse , & ett_pcp_pmns_subtype , & ett_pcp_pmns_namelen , & ett_pcp_pmns_name , & ett_pcp_pmns_names , & ett_pcp_pmns_names_nstrbytes , & ett_pcp_pmns_names_numstatus , & ett_pcp_pmns_names_numnames , & ett_pcp_pmns_names_nametree , & ett_pcp_pmns_names_nametree_status , & ett_pcp_pmns_names_nametree_namelen , & ett_pcp_pmns_names_nametree_name , & ett_pcp_pmns_ids , & ett_pcp_pmns_ids_status , & ett_pcp_pmns_ids_numids , & ett_pcp_pmns_child , & ett_pcp_pmid , & ett_pcp_pmid_flag , & ett_pcp_pmid_domain , & ett_pcp_pmid_cluster , & ett_pcp_pmid_item , & ett_pcp_pmid_type , & ett_pcp_pmid_sem , & ett_pcp_profile , & ett_pcp_ctxnum , & ett_pcp_profile_g_state , & ett_pcp_profile_numprof , & ett_pcp_profile_profile , & ett_pcp_profile_profile_state , & ett_pcp_profile_profile_numinst , & ett_pcp_fetch , & ett_pcp_fetch_numpmid , & ett_pcp_when , & ett_pcp_when_sec , & ett_pcp_when_usec , & ett_pcp_desc_req , & ett_pcp_units , & ett_pcp_units_dimspace , & ett_pcp_units_dimtime , & ett_pcp_units_dimcount , & ett_pcp_units_scalespace , & ett_pcp_units_scaletime , & ett_pcp_units_scalecount , & ett_pcp_instance , & ett_pcp_instance_req , & ett_pcp_instance_namelen , & ett_pcp_instance_name , & ett_pcp_instance_indom , & ett_pcp_instance_inst , & ett_pcp_instance_valoffset , & ett_pcp_instance_vallength , & ett_pcp_instance_value_insitu , & ett_pcp_instance_value_ptr , & ett_pcp_instance_value_int , & ett_pcp_instance_value_uint , & ett_pcp_instance_value_int64 , & ett_pcp_instance_value_uint64 , & ett_pcp_instance_value_float , & ett_pcp_instance_value_double , & ett_pcp_instance_value_aggr , & ett_pcp_instances , & ett_pcp_instances_numinst , & ett_pcp_results , & ett_pcp_results_numpmid , & ett_pcp_result , & ett_pcp_result_numval , & ett_pcp_result_valfmt , & ett_pcp_text_req , & ett_pcp_text_type , & ett_pcp_text_type_format , & ett_pcp_text_type_ident , & ett_pcp_text , & ett_pcp_text_ident , & ett_pcp_text_buflen , & ett_pcp_text_buffer , }
 ;
 static ei_register_info ei [ ] = {
 {
 & ei_pcp_type_event_unimplemented , {
 "pcp.pmid.type.event.unimplemented" , PI_UNDECODED , PI_WARN , "PM_TYPE_EVENT: Unimplemented Value Type" , EXPFILL }
 }
 , {
 & ei_pcp_type_nosupport_unsupported , {
 "pcp.pmid.type.nosupport.unsupported" , PI_UNDECODED , PI_WARN , "PM_TYPE_NOSUPPORT: Unsupported Value Type" , EXPFILL }
 }
 , {
 & ei_pcp_type_unknown_unknown_value , {
 "pcp.pmid.type.unknown.unknown_value" , PI_UNDECODED , PI_WARN , "PM_TYPE_UNKNOWN: Unknown Value Type" , EXPFILL }
 }
 , {
 & ei_pcp_unimplemented_value , {
 "pcp.pmid.type.unimplemented" , PI_UNDECODED , PI_WARN , "Unimplemented Value Type" , EXPFILL }
 }
 , {
 & ei_pcp_unimplemented_packet_type , {
 "pcp.type.unimplemented" , PI_UNDECODED , PI_WARN , "Unimplemented Packet Type" , EXPFILL }
 }
 , {
 & ei_pcp_ssl_upgrade , {
 "pcp.ssl_upgrade" , PI_COMMENTS_GROUP , PI_COMMENT , "SSL upgrade via SECURE_ACK" , EXPFILL }
 }
 , {
 & ei_pcp_ssl_upgrade_failed , {
 "pcp.ssl_upgrade_failed" , PI_RESPONSE_CODE , PI_WARN , "SSL upgrade via SECURE_ACK failed" , EXPFILL }
 }
 , }
 ;
 expert_module_t * expert_pcp ;
 expert_pcp = expert_register_protocol ( proto_pcp ) ;
 expert_register_field_array ( expert_pcp , ei , array_length ( ei ) ) ;
 proto_pcp = proto_register_protocol ( "Performance Co-Pilot" , "PCP" , "pcp" ) ;
 proto_register_field_array ( proto_pcp , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 pcp_handle = register_dissector ( "pcp" , dissect_pcp , proto_pcp ) ;
 }