static inline float pow_m1_4 ( WMACodecContext * s , float x ) {
 union {
 float f ;
 unsigned int v ;
 }
 u , t ;
 unsigned int e , m ;
 float a , b ;
 u . f = x ;
 e = u . v >> 23 ;
 m = ( u . v >> ( 23 - LSP_POW_BITS ) ) & ( ( 1 << LSP_POW_BITS ) - 1 ) ;
 t . v = ( ( u . v << LSP_POW_BITS ) & ( ( 1 << 23 ) - 1 ) ) | ( 127 << 23 ) ;
 a = s -> lsp_pow_m_table1 [ m ] ;
 b = s -> lsp_pow_m_table2 [ m ] ;
 return s -> lsp_pow_e_table [ e ] * ( a + b * t . f ) ;
 }