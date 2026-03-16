static UBool makeToUTable ( CnvExtData * extData , UCMTable * table ) {
 int32_t toUCount ;
 toUCount = reduceToUMappings ( table ) ;
 extData -> toUTable = utm_open ( "cnv extension toUTable" , 0x10000 , UCNV_EXT_TO_U_MIN_CODE_POINT , 4 ) ;
 extData -> toUUChars = utm_open ( "cnv extension toUUChars" , 0x10000 , UCNV_EXT_TO_U_INDEX_MASK + 1 , 2 ) ;
 return generateToUTable ( extData , table , 0 , toUCount , 0 , 0 ) ;
 }