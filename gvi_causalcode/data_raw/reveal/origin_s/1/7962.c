static UConverter * _HZ_SafeClone ( const UConverter * cnv , void * stackBuffer , int32_t * pBufferSize , UErrorCode * status ) {
 struct cloneHZStruct * localClone ;
 int32_t size , bufferSizeNeeded = sizeof ( struct cloneHZStruct ) ;
 if ( U_FAILURE ( * status ) ) {
 return 0 ;
 }
 if ( * pBufferSize == 0 ) {
 * pBufferSize = bufferSizeNeeded ;
 return 0 ;
 }
 localClone = ( struct cloneHZStruct * ) stackBuffer ;
 uprv_memcpy ( & localClone -> mydata , cnv -> extraInfo , sizeof ( UConverterDataHZ ) ) ;
 localClone -> cnv . extraInfo = & localClone -> mydata ;
 localClone -> cnv . isExtraLocal = TRUE ;
 size = ( int32_t ) ( sizeof ( UConverter ) + sizeof ( UAlignedMemory ) ) ;
 ( ( UConverterDataHZ * ) localClone -> cnv . extraInfo ) -> gbConverter = ucnv_safeClone ( ( ( UConverterDataHZ * ) cnv -> extraInfo ) -> gbConverter , & localClone -> subCnv , & size , status ) ;
 return & localClone -> cnv ;
 }