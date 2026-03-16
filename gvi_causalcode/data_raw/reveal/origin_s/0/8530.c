static gboolean gsm_a_stat_packet ( void * tapdata , const void * gatr_ptr , guint8 pdu_type , int protocol_disc ) {
 new_stat_data_t * stat_data = ( new_stat_data_t * ) tapdata ;
 const gsm_a_tap_rec_t * gatr = ( const gsm_a_tap_rec_t * ) gatr_ptr ;
 new_stat_tap_table * table ;
 stat_tap_table_item_type * msg_data ;
 guint i = 0 ;
 if ( gatr -> pdu_type != pdu_type ) return FALSE ;
 if ( pdu_type == BSSAP_PDU_TYPE_DTAP && ( int ) gatr -> protocol_disc != protocol_disc ) return FALSE ;
 if ( pdu_type == GSM_A_PDU_TYPE_SACCH && gatr -> protocol_disc != 0 ) return FALSE ;
 table = g_array_index ( stat_data -> new_stat_tap_data -> tables , new_stat_tap_table * , i ) ;
 msg_data = new_stat_tap_get_field_data ( table , gatr -> message_type , COUNT_COLUMN ) ;
 msg_data -> value . uint_value ++ ;
 new_stat_tap_set_field_data ( table , gatr -> message_type , COUNT_COLUMN , msg_data ) ;
 return TRUE ;
 }