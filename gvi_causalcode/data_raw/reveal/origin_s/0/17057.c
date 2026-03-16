static void qemuMonitorJSONHandleVNC ( qemuMonitorPtr mon , virJSONValuePtr data , int phase ) {
 const char * localNode , * localService , * localFamily ;
 const char * remoteNode , * remoteService , * remoteFamily ;
 const char * authScheme , * saslUsername , * x509dname ;
 int localFamilyID , remoteFamilyID ;
 virJSONValuePtr client ;
 virJSONValuePtr server ;
 if ( ! ( client = virJSONValueObjectGet ( data , "client" ) ) ) {
 VIR_WARN ( "missing client info in VNC event" ) ;
 return ;
 }
 if ( ! ( server = virJSONValueObjectGet ( data , "server" ) ) ) {
 VIR_WARN ( "missing server info in VNC event" ) ;
 return ;
 }
 authScheme = virJSONValueObjectGetString ( server , "auth" ) ;
 localFamily = virJSONValueObjectGetString ( server , "family" ) ;
 localNode = virJSONValueObjectGetString ( server , "host" ) ;
 localService = virJSONValueObjectGetString ( server , "service" ) ;
 remoteFamily = virJSONValueObjectGetString ( client , "family" ) ;
 remoteNode = virJSONValueObjectGetString ( client , "host" ) ;
 remoteService = virJSONValueObjectGetString ( client , "service" ) ;
 saslUsername = virJSONValueObjectGetString ( client , "sasl_username" ) ;
 x509dname = virJSONValueObjectGetString ( client , "x509_dname" ) ;
 if ( ( localFamilyID = qemuMonitorGraphicsAddressFamilyTypeFromString ( localFamily ) ) < 0 ) {
 VIR_WARN ( "unknown address family '%s'" , localFamily ) ;
 localFamilyID = VIR_DOMAIN_EVENT_GRAPHICS_ADDRESS_IPV4 ;
 }
 if ( ( remoteFamilyID = qemuMonitorGraphicsAddressFamilyTypeFromString ( remoteFamily ) ) < 0 ) {
 VIR_WARN ( "unknown address family '%s'" , remoteFamily ) ;
 remoteFamilyID = VIR_DOMAIN_EVENT_GRAPHICS_ADDRESS_IPV4 ;
 }
 qemuMonitorEmitGraphics ( mon , phase , localFamilyID , localNode , localService , remoteFamilyID , remoteNode , remoteService , authScheme , x509dname , saslUsername ) ;
 }