int vp9_block_energy ( VP9_COMP * cpi , MACROBLOCK * x , BLOCK_SIZE bs ) {
 double energy ;
 unsigned int var = block_variance ( cpi , x , bs ) ;
 vp9_clear_system_state ( ) ;
 energy = 0.9 * ( log ( var + 1.0 ) - 10.0 ) ;
 return clamp ( ( int ) round ( energy ) , ENERGY_MIN , ENERGY_MAX ) ;
 }