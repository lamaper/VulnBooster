static void _CompoundTextOpen ( UConverter * cnv , UConverterLoadArgs * pArgs , UErrorCode * errorCode ) {
 cnv -> extraInfo = uprv_malloc ( sizeof ( UConverterDataCompoundText ) ) ;
 if ( cnv -> extraInfo != NULL ) {
 UConverterDataCompoundText * myConverterData = ( UConverterDataCompoundText * ) cnv -> extraInfo ;
 UConverterNamePieces stackPieces ;
 UConverterLoadArgs stackArgs = {
 ( int32_t ) sizeof ( UConverterLoadArgs ) }
 ;
 myConverterData -> myConverterArray [ COMPOUND_TEXT_SINGLE_0 ] = NULL ;
 myConverterData -> myConverterArray [ COMPOUND_TEXT_SINGLE_1 ] = ucnv_loadSharedData ( "icu-internal-compound-s1" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ COMPOUND_TEXT_SINGLE_2 ] = ucnv_loadSharedData ( "icu-internal-compound-s2" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ COMPOUND_TEXT_SINGLE_3 ] = ucnv_loadSharedData ( "icu-internal-compound-s3" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ COMPOUND_TEXT_DOUBLE_1 ] = ucnv_loadSharedData ( "icu-internal-compound-d1" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ COMPOUND_TEXT_DOUBLE_2 ] = ucnv_loadSharedData ( "icu-internal-compound-d2" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ COMPOUND_TEXT_DOUBLE_3 ] = ucnv_loadSharedData ( "icu-internal-compound-d3" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ COMPOUND_TEXT_DOUBLE_4 ] = ucnv_loadSharedData ( "icu-internal-compound-d4" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ COMPOUND_TEXT_DOUBLE_5 ] = ucnv_loadSharedData ( "icu-internal-compound-d5" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ COMPOUND_TEXT_DOUBLE_6 ] = ucnv_loadSharedData ( "icu-internal-compound-d6" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ COMPOUND_TEXT_DOUBLE_7 ] = ucnv_loadSharedData ( "icu-internal-compound-d7" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ COMPOUND_TEXT_TRIPLE_DOUBLE ] = ucnv_loadSharedData ( "icu-internal-compound-t" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ IBM_915 ] = ucnv_loadSharedData ( "ibm-915_P100-1995" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ IBM_916 ] = ucnv_loadSharedData ( "ibm-916_P100-1995" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ IBM_914 ] = ucnv_loadSharedData ( "ibm-914_P100-1995" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ IBM_874 ] = ucnv_loadSharedData ( "ibm-874_P100-1995" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ IBM_912 ] = ucnv_loadSharedData ( "ibm-912_P100-1995" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ IBM_913 ] = ucnv_loadSharedData ( "ibm-913_P100-2000" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ ISO_8859_14 ] = ucnv_loadSharedData ( "iso-8859_14-1998" , & stackPieces , & stackArgs , errorCode ) ;
 myConverterData -> myConverterArray [ IBM_923 ] = ucnv_loadSharedData ( "ibm-923_P100-1998" , & stackPieces , & stackArgs , errorCode ) ;
 if ( U_FAILURE ( * errorCode ) || pArgs -> onlyTestIsLoadable ) {
 _CompoundTextClose ( cnv ) ;
 return ;
 }
 myConverterData -> state = ( COMPOUND_TEXT_CONVERTERS ) 0 ;
 }
 else {
 * errorCode = U_MEMORY_ALLOCATION_ERROR ;
 }
 }