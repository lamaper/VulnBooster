NON_EXPORTED_BASE ( public blink : : Platform ) {
 public : ~ TestBlinkPlatformSupport ( ) override ;
 void cryptographicallyRandomValues ( unsigned char * buffer , size_t length ) override ;
 const unsigned char * getTraceCategoryEnabledFlag ( const char * categoryName ) override ;
 blink : : WebThread * currentThread ( ) override {
 return & m_currentThread ;
 }
 private : CurrentThreadMock m_currentThread ;
 }