static void dec_lpc_spectrum_inv ( TwinContext * tctx , float * lsp , enum FrameType ftype , float * lpc ) {
 int i ;
 int size = tctx -> mtab -> size / tctx -> mtab -> fmode [ ftype ] . sub ;
 for ( i = 0 ;
 i < tctx -> mtab -> n_lsp ;
 i ++ ) lsp [ i ] = 2 * cos ( lsp [ i ] ) ;
 switch ( ftype ) {
 case FT_LONG : eval_lpcenv_2parts ( tctx , ftype , lsp , lpc , size , 8 ) ;
 break ;
 case FT_MEDIUM : eval_lpcenv_2parts ( tctx , ftype , lsp , lpc , size , 2 ) ;
 break ;
 case FT_SHORT : eval_lpcenv ( tctx , lsp , lpc ) ;
 break ;
 }
 }