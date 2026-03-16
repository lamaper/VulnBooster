static void decode_gains ( const uint8_t vq_gain , const enum Mode mode , float * fixed_gain_factor , float * pitch_gain ) {
 const int16_t * gains = ( mode <= MODE_8k85 ? qua_gain_6b [ vq_gain ] : qua_gain_7b [ vq_gain ] ) ;
 * pitch_gain = gains [ 0 ] * ( 1.0f / ( 1 << 14 ) ) ;
 * fixed_gain_factor = gains [ 1 ] * ( 1.0f / ( 1 << 11 ) ) ;
 }