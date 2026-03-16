void proto_register_nlm ( void ) {
 static hf_register_info hf [ ] = {
 {
 & hf_nlm_procedure_v1 , {
 "V1 Procedure" , "nlm.procedure_v1" , FT_UINT32 , BASE_DEC , VALS ( nlm1_proc_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_procedure_v2 , {
 "V2 Procedure" , "nlm.procedure_v2" , FT_UINT32 , BASE_DEC , VALS ( nlm2_proc_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_procedure_v3 , {
 "V3 Procedure" , "nlm.procedure_v3" , FT_UINT32 , BASE_DEC , VALS ( nlm3_proc_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_procedure_v4 , {
 "V4 Procedure" , "nlm.procedure_v4" , FT_UINT32 , BASE_DEC , VALS ( nlm4_proc_vals ) , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_cookie , {
 "cookie" , "nlm.cookie" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_block , {
 "block" , "nlm.block" , FT_BOOLEAN , BASE_NONE , TFS ( & tfs_yes_no ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_nlm_exclusive , {
 "exclusive" , "nlm.exclusive" , FT_BOOLEAN , BASE_NONE , TFS ( & tfs_yes_no ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_nlm_lock , {
 "lock" , "nlm.lock" , FT_NONE , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_lock_caller_name , {
 "caller_name" , "nlm.lock.caller_name" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_lock_owner , {
 "owner" , "nlm.lock.owner" , FT_BYTES , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_lock_svid , {
 "svid" , "nlm.lock.svid" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_lock_l_offset64 , {
 "l_offset" , "nlm.lock.l_offset" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_lock_l_offset , {
 "l_offset" , "nlm.lock.l_offset" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_lock_l_len64 , {
 "l_len" , "nlm.lock.l_len" , FT_UINT64 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_lock_l_len , {
 "l_len" , "nlm.lock.l_len" , FT_UINT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_reclaim , {
 "reclaim" , "nlm.reclaim" , FT_BOOLEAN , BASE_NONE , TFS ( & tfs_yes_no ) , 0x0 , NULL , HFILL }
 }
 , {
 & hf_nlm_state , {
 "state" , "nlm.state" , FT_UINT32 , BASE_DEC , NULL , 0 , "STATD state" , HFILL }
 }
 , {
 & hf_nlm_stat , {
 "stat" , "nlm.stat" , FT_UINT32 , BASE_DEC , VALS ( names_nlm_stats ) , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_test_stat , {
 "test_stat" , "nlm.test_stat" , FT_NONE , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_test_stat_stat , {
 "stat" , "nlm.test_stat.stat" , FT_UINT32 , BASE_DEC , VALS ( names_nlm_stats ) , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_holder , {
 "holder" , "nlm.holder" , FT_NONE , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_share , {
 "share" , "nlm.share" , FT_NONE , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_share_mode , {
 "mode" , "nlm.share.mode" , FT_UINT32 , BASE_DEC , VALS ( names_fsh_mode ) , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_share_access , {
 "access" , "nlm.share.access" , FT_UINT32 , BASE_DEC , VALS ( names_fsh_access ) , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_share_name , {
 "name" , "nlm.share.name" , FT_STRING , BASE_NONE , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_sequence , {
 "sequence" , "nlm.sequence" , FT_INT32 , BASE_DEC , NULL , 0 , NULL , HFILL }
 }
 , {
 & hf_nlm_request_in , {
 "Request MSG in" , "nlm.msg_in" , FT_UINT32 , BASE_DEC , NULL , 0 , "The RES packet is a response to the MSG in this packet" , HFILL }
 }
 , {
 & hf_nlm_reply_in , {
 "Reply RES in" , "nlm.res_in" , FT_UINT32 , BASE_DEC , NULL , 0 , "The response to this MSG packet is in this packet" , HFILL }
 }
 , {
 & hf_nlm_time , {
 "Time from request" , "nlm.time" , FT_RELATIVE_TIME , BASE_NONE , NULL , 0 , "Time between Request and Reply for async NLM calls" , HFILL }
 }
 , }
 ;
 static gint * ett [ ] = {
 & ett_nlm , & ett_nlm_lock , }
 ;
 module_t * nlm_module ;
 proto_nlm = proto_register_protocol ( "Network Lock Manager Protocol" , "NLM" , "nlm" ) ;
 proto_register_field_array ( proto_nlm , hf , array_length ( hf ) ) ;
 proto_register_subtree_array ( ett , array_length ( ett ) ) ;
 nlm_module = prefs_register_protocol ( proto_nlm , NULL ) ;
 prefs_register_bool_preference ( nlm_module , "msg_res_matching" , "Match MSG/RES packets for async NLM" , "Whether the dissector will track and match MSG and RES calls for asynchronous NLM" , & nlm_match_msgres ) ;
 register_init_routine ( nlm_msg_res_match_init ) ;
 register_cleanup_routine ( nlm_msg_res_match_cleanup ) ;
 }