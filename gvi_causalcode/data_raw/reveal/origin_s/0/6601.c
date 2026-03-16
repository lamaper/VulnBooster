static ulmbcs_byte_t FindLMBCSUniRange ( UChar uniChar ) {
 const struct _UniLMBCSGrpMap * pTable = UniLMBCSGrpMap ;
 while ( uniChar > pTable -> uniEndRange ) {
 pTable ++ ;
 }
 if ( uniChar >= pTable -> uniStartRange ) {
 return pTable -> GrpType ;
 }
 return ULMBCS_GRP_UNICODE ;
 }