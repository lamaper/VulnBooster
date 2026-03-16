static void eval_lpcenv ( TwinContext * tctx , const float * cos_vals , float * lpc ) {
 int i ;
 const ModeTab * mtab = tctx -> mtab ;
 int size_s = mtab -> size / mtab -> fmode [ FT_SHORT ] . sub ;
 for ( i = 0 ;
 i < size_s / 2 ;
 i ++ ) {
 float cos_i = tctx -> cos_tabs [ 0 ] [ i ] ;
 lpc [ i ] = eval_lpc_spectrum ( cos_vals , cos_i , mtab -> n_lsp ) ;
 lpc [ size_s - i - 1 ] = eval_lpc_spectrum ( cos_vals , - cos_i , mtab -> n_lsp ) ;
 }
 }