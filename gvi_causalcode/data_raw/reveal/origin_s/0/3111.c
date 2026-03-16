static UBool CnvExtAddTable ( NewConverter * cnvData , UCMTable * table , UConverterStaticData * staticData ) {
 CnvExtData * extData ;
 if ( table -> unicodeMask & UCNV_HAS_SURROGATES ) {
 fprintf ( stderr , "error: contains mappings for surrogate code points\n" ) ;
 return FALSE ;
 }
 staticData -> conversionType = UCNV_MBCS ;
 extData = ( CnvExtData * ) cnvData ;
 return makeToUTable ( extData , table ) && makeFromUTable ( extData , table ) ;
 }