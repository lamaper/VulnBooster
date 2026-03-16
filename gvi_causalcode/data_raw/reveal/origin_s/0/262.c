static void call_avp_subdissector ( guint32 vendorid , guint32 code , tvbuff_t * subtvb , packet_info * pinfo , proto_tree * avp_tree , diam_sub_dis_t * diam_sub_dis_inf ) {
 TRY {
 switch ( vendorid ) {
 case 0 : dissector_try_uint_new ( diameter_dissector_table , code , subtvb , pinfo , avp_tree , FALSE , diam_sub_dis_inf ) ;
 break ;
 case VENDOR_ERICSSON : dissector_try_uint_new ( diameter_ericsson_avp_dissector_table , code , subtvb , pinfo , avp_tree , FALSE , diam_sub_dis_inf ) ;
 break ;
 case VENDOR_THE3GPP : dissector_try_uint_new ( diameter_3gpp_avp_dissector_table , code , subtvb , pinfo , avp_tree , FALSE , diam_sub_dis_inf ) ;
 break ;
 default : break ;
 }
 }
 CATCH_NONFATAL_ERRORS {
 show_exception ( subtvb , pinfo , avp_tree , EXCEPT_CODE , GET_MESSAGE ) ;
 }
 ENDTRY ;
 }