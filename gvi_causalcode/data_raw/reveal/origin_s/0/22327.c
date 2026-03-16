static int32_t ucnv_convertAlgorithmic ( UBool convertToAlgorithmic , UConverterType algorithmicType , UConverter * cnv , char * target , int32_t targetCapacity , const char * source , int32_t sourceLength , UErrorCode * pErrorCode ) {
 UConverter algoConverterStatic ;
 UConverter * algoConverter , * to , * from ;
 int32_t targetLength ;
 if ( pErrorCode == NULL || U_FAILURE ( * pErrorCode ) ) {
 return 0 ;
 }
 if ( cnv == NULL || source == NULL || sourceLength < - 1 || targetCapacity < 0 || ( targetCapacity > 0 && target == NULL ) ) {
 * pErrorCode = U_ILLEGAL_ARGUMENT_ERROR ;
 return 0 ;
 }
 if ( sourceLength == 0 || ( sourceLength < 0 && * source == 0 ) ) {
 return u_terminateChars ( target , targetCapacity , 0 , pErrorCode ) ;
 }
 algoConverter = ucnv_createAlgorithmicConverter ( & algoConverterStatic , algorithmicType , "" , 0 , pErrorCode ) ;
 if ( U_FAILURE ( * pErrorCode ) ) {
 return 0 ;
 }
 if ( convertToAlgorithmic ) {
 ucnv_resetToUnicode ( cnv ) ;
 to = algoConverter ;
 from = cnv ;
 }
 else {
 ucnv_resetFromUnicode ( cnv ) ;
 from = algoConverter ;
 to = cnv ;
 }
 targetLength = ucnv_internalConvert ( to , from , target , targetCapacity , source , sourceLength , pErrorCode ) ;
 ucnv_close ( algoConverter ) ;
 return targetLength ;
 }