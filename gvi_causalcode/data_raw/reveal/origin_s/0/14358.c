static void setTrailingWSStart ( UBiDi * pBiDi ) {
 const DirProp * dirProps = pBiDi -> dirProps ;
 UBiDiLevel * levels = pBiDi -> levels ;
 int32_t start = pBiDi -> length ;
 UBiDiLevel paraLevel = pBiDi -> paraLevel ;
 if ( dirProps [ start - 1 ] == B ) {
 pBiDi -> trailingWSStart = start ;
 return ;
 }
 while ( start > 0 && DIRPROP_FLAG ( dirProps [ start - 1 ] ) & MASK_WS ) {
 -- start ;
 }
 while ( start > 0 && levels [ start - 1 ] == paraLevel ) {
 -- start ;
 }
 pBiDi -> trailingWSStart = start ;
 }