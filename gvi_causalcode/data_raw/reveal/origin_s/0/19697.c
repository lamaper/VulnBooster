static void dec_gain ( TwinContext * tctx , GetBitContext * gb , enum FrameType ftype , float * out ) {
 const ModeTab * mtab = tctx -> mtab ;
 int i , j ;
 int sub = mtab -> fmode [ ftype ] . sub ;
 float step = AMP_MAX / ( ( 1 << GAIN_BITS ) - 1 ) ;
 float sub_step = SUB_AMP_MAX / ( ( 1 << SUB_GAIN_BITS ) - 1 ) ;
 if ( ftype == FT_LONG ) {
 for ( i = 0 ;
 i < tctx -> avctx -> channels ;
 i ++ ) out [ i ] = ( 1. / ( 1 << 13 ) ) * mulawinv ( step * 0.5 + step * get_bits ( gb , GAIN_BITS ) , AMP_MAX , MULAW_MU ) ;
 }
 else {
 for ( i = 0 ;
 i < tctx -> avctx -> channels ;
 i ++ ) {
 float val = ( 1. / ( 1 << 23 ) ) * mulawinv ( step * 0.5 + step * get_bits ( gb , GAIN_BITS ) , AMP_MAX , MULAW_MU ) ;
 for ( j = 0 ;
 j < sub ;
 j ++ ) {
 out [ i * sub + j ] = val * mulawinv ( sub_step * 0.5 + sub_step * get_bits ( gb , SUB_GAIN_BITS ) , SUB_AMP_MAX , MULAW_MU ) ;
 }
 }
 }
 }