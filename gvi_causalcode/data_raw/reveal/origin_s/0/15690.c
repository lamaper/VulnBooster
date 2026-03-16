static void update_sub_state ( AMRWBContext * ctx ) {
 memmove ( & ctx -> excitation_buf [ 0 ] , & ctx -> excitation_buf [ AMRWB_SFR_SIZE ] , ( AMRWB_P_DELAY_MAX + LP_ORDER + 1 ) * sizeof ( float ) ) ;
 memmove ( & ctx -> pitch_gain [ 1 ] , & ctx -> pitch_gain [ 0 ] , 5 * sizeof ( float ) ) ;
 memmove ( & ctx -> fixed_gain [ 1 ] , & ctx -> fixed_gain [ 0 ] , 1 * sizeof ( float ) ) ;
 memmove ( & ctx -> samples_az [ 0 ] , & ctx -> samples_az [ AMRWB_SFR_SIZE ] , LP_ORDER * sizeof ( float ) ) ;
 memmove ( & ctx -> samples_up [ 0 ] , & ctx -> samples_up [ AMRWB_SFR_SIZE ] , UPS_MEM_SIZE * sizeof ( float ) ) ;
 memmove ( & ctx -> samples_hb [ 0 ] , & ctx -> samples_hb [ AMRWB_SFR_SIZE_16k ] , LP_ORDER_16k * sizeof ( float ) ) ;
 }