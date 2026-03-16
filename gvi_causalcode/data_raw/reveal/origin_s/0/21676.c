static void decode_pitch_vector ( AMRContext * p , const AMRNBSubframe * amr_subframe , const int subframe ) {
 int pitch_lag_int , pitch_lag_frac ;
 enum Mode mode = p -> cur_frame_mode ;
 if ( p -> cur_frame_mode == MODE_12k2 ) {
 decode_pitch_lag_1_6 ( & pitch_lag_int , & pitch_lag_frac , amr_subframe -> p_lag , p -> pitch_lag_int , subframe ) ;
 }
 else ff_decode_pitch_lag ( & pitch_lag_int , & pitch_lag_frac , amr_subframe -> p_lag , p -> pitch_lag_int , subframe , mode != MODE_4k75 && mode != MODE_5k15 , mode <= MODE_6k7 ? 4 : ( mode == MODE_7k95 ? 5 : 6 ) ) ;
 p -> pitch_lag_int = pitch_lag_int ;
 pitch_lag_frac <<= ( p -> cur_frame_mode != MODE_12k2 ) ;
 pitch_lag_int += pitch_lag_frac > 0 ;
 ff_acelp_interpolatef ( p -> excitation , p -> excitation + 1 - pitch_lag_int , ff_b60_sinc , 6 , pitch_lag_frac + 6 - 6 * ( pitch_lag_frac > 0 ) , 10 , AMR_SUBFRAME_SIZE ) ;
 memcpy ( p -> pitch_vector , p -> excitation , AMR_SUBFRAME_SIZE * sizeof ( float ) ) ;
 }