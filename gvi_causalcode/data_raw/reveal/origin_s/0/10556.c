static gboolean h225_stat_packet ( void * tapdata , packet_info * pinfo _U_ , epan_dissect_t * edt _U_ , const void * hpi_ptr ) {
 new_stat_data_t * stat_data = ( new_stat_data_t * ) tapdata ;
 const h225_packet_info * hpi = ( const h225_packet_info * ) hpi_ptr ;
 int tag_idx = - 1 ;
 int reason_idx = - 1 ;
 if ( hpi -> msg_tag < 0 ) {
 return FALSE ;
 }
 switch ( hpi -> msg_type ) {
 case H225_RAS : tag_idx = ras_msg_idx [ MIN ( hpi -> msg_tag , ( int ) RAS_MSG_TYPES - 1 ) ] ;
 if ( hpi -> reason < 0 ) {
 break ;
 }
 switch ( hpi -> msg_tag ) {
 case 2 : reason_idx = grj_reason_idx [ MIN ( hpi -> reason , ( int ) GRJ_REASONS - 1 ) ] ;
 break ;
 case 5 : reason_idx = rrj_reason_idx [ MIN ( hpi -> reason , ( int ) RRJ_REASONS - 1 ) ] ;
 break ;
 case 6 : reason_idx = urq_reason_idx [ MIN ( hpi -> reason , ( int ) URQ_REASONS - 1 ) ] ;
 break ;
 case 8 : reason_idx = urj_reason_idx [ MIN ( hpi -> reason , ( int ) URJ_REASONS - 1 ) ] ;
 break ;
 case 11 : reason_idx = arj_reason_idx [ MIN ( hpi -> reason , ( int ) ARJ_REASONS - 1 ) ] ;
 break ;
 case 14 : reason_idx = brj_reason_idx [ MIN ( hpi -> reason , ( int ) BRJ_REASONS - 1 ) ] ;
 break ;
 case 15 : reason_idx = drq_reason_idx [ MIN ( hpi -> reason , ( int ) DRQ_REASONS - 1 ) ] ;
 break ;
 case 17 : reason_idx = drj_reason_idx [ MIN ( hpi -> reason , ( int ) DRJ_REASONS - 1 ) ] ;
 break ;
 case 20 : reason_idx = lrj_reason_idx [ MIN ( hpi -> reason , ( int ) LRJ_REASONS - 1 ) ] ;
 break ;
 case 29 : reason_idx = irqnak_reason_idx [ MIN ( hpi -> reason , ( int ) IRQNAK_REASONS - 1 ) ] ;
 break ;
 default : break ;
 }
 break ;
 case H225_CS : tag_idx = cs_msg_idx [ MIN ( hpi -> msg_tag , ( int ) CS_MSG_TYPES - 1 ) ] ;
 if ( hpi -> reason < 0 ) {
 break ;
 }
 switch ( hpi -> msg_tag ) {
 case 5 : reason_idx = rel_cmp_reason_idx [ MIN ( hpi -> reason , ( int ) REL_CMP_REASONS - 1 ) ] ;
 break ;
 case 6 : reason_idx = facility_reason_idx [ MIN ( hpi -> reason , ( int ) FACILITY_REASONS - 1 ) ] ;
 break ;
 default : break ;
 }
 break ;
 case H225_OTHERS : default : tag_idx = other_idx ;
 }
 if ( tag_idx >= 0 ) {
 stat_tap_table * table = g_array_index ( stat_data -> stat_tap_data -> tables , stat_tap_table * , 0 ) ;
 stat_tap_table_item_type * msg_data = new_stat_tap_get_field_data ( table , tag_idx , COUNT_COLUMN ) ;
 ;
 msg_data -> value . uint_value ++ ;
 new_stat_tap_set_field_data ( table , tag_idx , COUNT_COLUMN , msg_data ) ;
 if ( reason_idx >= 0 ) {
 msg_data = new_stat_tap_get_field_data ( table , reason_idx , COUNT_COLUMN ) ;
 ;
 msg_data -> value . uint_value ++ ;
 new_stat_tap_set_field_data ( table , reason_idx , COUNT_COLUMN , msg_data ) ;
 }
 return TRUE ;
 }
 return FALSE ;
 }