static const char * proto_avp ( diam_ctx_t * c , diam_avp_t * a , tvbuff_t * tvb , diam_sub_dis_t * diam_sub_dis_inf ) {
 proto_avp_t * t = ( proto_avp_t * ) a -> type_data ;
 col_set_writable ( c -> pinfo -> cinfo , FALSE ) ;
 if ( ! t -> handle ) {
 t -> handle = find_dissector ( t -> name ) ;
 if ( ! t -> handle ) t -> handle = data_handle ;
 }
 TRY {
 call_dissector_with_data ( t -> handle , tvb , c -> pinfo , c -> tree , diam_sub_dis_inf ) ;
 }
 CATCH_NONFATAL_ERRORS {
 show_exception ( tvb , c -> pinfo , c -> tree , EXCEPT_CODE , GET_MESSAGE ) ;
 }
 ENDTRY ;
 return "" ;
 }