static gboolean gsm_a_sacch_rr_stat_packet ( void * tapdata , packet_info * pinfo _U_ , epan_dissect_t * edt _U_ , const void * gatr_ptr ) {
 return gsm_a_stat_packet ( tapdata , gatr_ptr , GSM_A_PDU_TYPE_SACCH , 0 ) ;
 }