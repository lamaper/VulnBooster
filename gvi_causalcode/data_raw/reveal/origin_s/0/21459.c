static void saturate_output_float ( COOKContext * q , float * out ) {
 q -> dsp . vector_clipf ( out , q -> mono_mdct_output + q -> samples_per_channel , - 1.0f , 1.0f , FFALIGN ( q -> samples_per_channel , 8 ) ) ;
 }