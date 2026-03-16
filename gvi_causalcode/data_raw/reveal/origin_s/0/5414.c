static int mtp3_calls_packet ( void * ptr _U_ , packet_info * pinfo , epan_dissect_t * edt _U_ , const void * mtp3_info _U_ ) {
 const mtp3_tap_rec_t * pi = ( const mtp3_tap_rec_t * ) mtp3_info ;
 mtp3_opc = pi -> addr_opc . pc ;
 mtp3_dpc = pi -> addr_dpc . pc ;
 mtp3_ni = pi -> addr_opc . ni ;
 mtp3_frame_num = pinfo -> fd -> num ;
 return 0 ;
 }