int ztoken_handle_comment ( i_ctx_t * i_ctx_p , scanner_state * sstate , const ref * ptoken , int scan_code , bool save , bool push_file , op_proc_t cont ) {
 const char * proc_name ;
 scanner_state * pstate ;
 os_ptr op ;
 ref * ppcproc ;
 int code ;
 switch ( scan_code ) {
 case scan_Comment : proc_name = "%ProcessComment" ;
 break ;
 case scan_DSC_Comment : proc_name = "%ProcessDSCComment" ;
 break ;
 default : return_error ( gs_error_Fatal ) ;
 }
 if ( ostop - osp < 2 ) {
 code = ref_stack_extend ( & o_stack , 2 ) ;
 if ( code < 0 ) return code ;
 }
 check_estack ( 3 ) ;
 code = name_enter_string ( imemory , proc_name , esp + 3 ) ;
 if ( code < 0 ) return code ;
 if ( save ) {
 pstate = ( scanner_state * ) ialloc_struct ( scanner_state_dynamic , & st_scanner_state_dynamic , "ztoken_handle_comment" ) ;
 if ( pstate == 0 ) return_error ( gs_error_VMerror ) ;
 ( ( scanner_state_dynamic * ) pstate ) -> mem = imemory ;
 * pstate = * sstate ;
 }
 else pstate = sstate ;
 if ( ! pstate -> s_pstack ) osp [ 2 ] = * ptoken ;
 make_op_estack ( esp + 1 , cont ) ;
 make_istruct ( esp + 2 , 0 , pstate ) ;
 ppcproc = dict_find_name ( esp + 3 ) ;
 if ( ppcproc == 0 ) {
 if ( pstate -> s_pstack ) -- osp ;
 esp += 2 ;
 }
 else {
 if ( pstate -> s_pstack ) {
 op = ++ osp ;
 * op = op [ - 1 ] ;
 }
 else {
 op = osp += 2 ;
 }
 op [ - 1 ] = pstate -> s_file ;
 esp [ 3 ] = * ppcproc ;
 esp += 3 ;
 }
 return o_push_estack ;
 }