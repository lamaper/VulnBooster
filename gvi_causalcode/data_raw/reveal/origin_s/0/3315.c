static gboolean h225rassrt_packet ( void * phs , packet_info * pinfo _U_ , epan_dissect_t * edt _U_ , const void * phi ) {
 rtd_data_t * rtd_data = ( rtd_data_t * ) phs ;
 rtd_stat_table * rs = & rtd_data -> stat_table ;
 const h225_packet_info * pi = ( const h225_packet_info * ) phi ;
 ras_type rasmsg_type = RAS_OTHER ;
 ras_category rascategory = RAS_OTHERS ;
 if ( pi -> msg_type != H225_RAS || pi -> msg_tag == - 1 ) {
 return FALSE ;
 }
 if ( pi -> msg_tag < 21 ) {
 rascategory = ( ras_category ) ( pi -> msg_tag / 3 ) ;
 rasmsg_type = ( ras_type ) ( pi -> msg_tag % 3 ) ;
 }
 else {
 return FALSE ;
 }
 switch ( rasmsg_type ) {
 case RAS_REQUEST : if ( pi -> is_duplicate ) {
 rs -> time_stats [ rascategory ] . req_dup_num ++ ;
 }
 else {
 rs -> time_stats [ rascategory ] . open_req_num ++ ;
 }
 break ;
 case RAS_CONFIRM : case RAS_REJECT : if ( pi -> is_duplicate ) {
 rs -> time_stats [ rascategory ] . rsp_dup_num ++ ;
 }
 else if ( ! pi -> request_available ) {
 rs -> time_stats [ rascategory ] . disc_rsp_num ++ ;
 }
 else {
 rs -> time_stats [ rascategory ] . open_req_num -- ;
 time_stat_update ( & ( rs -> time_stats [ rascategory ] . rtd [ 0 ] ) , & ( pi -> delta_time ) , pinfo ) ;
 }
 break ;
 default : return FALSE ;
 }
 return TRUE ;
 }