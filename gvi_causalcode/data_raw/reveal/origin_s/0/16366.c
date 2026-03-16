TSPortDescriptor TSPortDescriptorParse ( const char * descriptor ) {
 HttpProxyPort * port = new HttpProxyPort ( ) ;
 if ( descriptor && port -> processOptions ( descriptor ) ) {
 return ( TSPortDescriptor ) port ;
 }
 delete port ;
 return nullptr ;
 }