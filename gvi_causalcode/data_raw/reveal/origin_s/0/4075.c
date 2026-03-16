static void qtmd_init_model ( struct qtmd_model * model , struct qtmd_modelsym * syms , int start , int len ) {
 int i ;
 model -> shiftsleft = 4 ;
 model -> entries = len ;
 model -> syms = syms ;
 for ( i = 0 ;
 i <= len ;
 i ++ ) {
 syms [ i ] . sym = start + i ;
 syms [ i ] . cumfreq = len - i ;
 }
 }