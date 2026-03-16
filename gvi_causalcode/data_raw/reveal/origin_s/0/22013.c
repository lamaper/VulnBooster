static COMPOUND_TEXT_CONVERTERS getState ( int codepoint ) {
 COMPOUND_TEXT_CONVERTERS state = DO_SEARCH ;
 if ( isASCIIRange ( codepoint ) ) {
 state = COMPOUND_TEXT_SINGLE_0 ;
 }
 else if ( isIBM912 ( codepoint ) ) {
 state = IBM_912 ;
 }
 else if ( isIBM913 ( codepoint ) ) {
 state = IBM_913 ;
 }
 else if ( isISO8859_14 ( codepoint ) ) {
 state = ISO_8859_14 ;
 }
 else if ( isIBM923 ( codepoint ) ) {
 state = IBM_923 ;
 }
 else if ( isIBM874 ( codepoint ) ) {
 state = IBM_874 ;
 }
 else if ( isIBM914 ( codepoint ) ) {
 state = IBM_914 ;
 }
 else if ( isCompoundS2 ( codepoint ) ) {
 state = COMPOUND_TEXT_SINGLE_2 ;
 }
 else if ( isCompoundS3 ( codepoint ) ) {
 state = COMPOUND_TEXT_SINGLE_3 ;
 }
 else if ( isIBM916 ( codepoint ) ) {
 state = IBM_916 ;
 }
 else if ( isIBM915 ( codepoint ) ) {
 state = IBM_915 ;
 }
 else if ( isCompoundS1 ( codepoint ) ) {
 state = COMPOUND_TEXT_SINGLE_1 ;
 }
 return state ;
 }