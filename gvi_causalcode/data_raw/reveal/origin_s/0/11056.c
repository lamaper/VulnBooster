int qemuAgentGetFSInfo ( qemuAgentPtr mon , virDomainFSInfoPtr * * info , virDomainDefPtr vmdef ) {
 size_t i , j , k ;
 int ret = - 1 ;
 ssize_t ndata = 0 , ndisk ;
 char * * alias ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 virJSONValuePtr data ;
 virDomainFSInfoPtr * info_ret = NULL ;
 virPCIDeviceAddress pci_address ;
 cmd = qemuAgentMakeCommand ( "guest-get-fsinfo" , NULL ) ;
 if ( ! cmd ) return ret ;
 if ( qemuAgentCommand ( mon , cmd , & reply , true , VIR_DOMAIN_QEMU_AGENT_COMMAND_BLOCK ) < 0 ) goto cleanup ;
 if ( ! ( data = virJSONValueObjectGet ( reply , "return" ) ) ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "guest-get-fsinfo reply was missing return data" ) ) ;
 goto cleanup ;
 }
 if ( data -> type != VIR_JSON_TYPE_ARRAY ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "guest-get-fsinfo return information was not " "an array" ) ) ;
 goto cleanup ;
 }
 ndata = virJSONValueArraySize ( data ) ;
 if ( ! ndata ) {
 ret = 0 ;
 * info = NULL ;
 goto cleanup ;
 }
 if ( VIR_ALLOC_N ( info_ret , ndata ) < 0 ) goto cleanup ;
 for ( i = 0 ;
 i < ndata ;
 i ++ ) {
 virJSONValuePtr entry = virJSONValueArrayGet ( data , ndata - 1 - i ) ;
 if ( ! entry ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "array element '%zd' of '%zd' missing in " "guest-get-fsinfo return data" ) , i , ndata ) ;
 goto cleanup ;
 }
 if ( VIR_ALLOC ( info_ret [ i ] ) < 0 ) goto cleanup ;
 if ( VIR_STRDUP ( info_ret [ i ] -> mountpoint , virJSONValueObjectGetString ( entry , "mountpoint" ) ) < 0 ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "'mountpoint' missing in reply of " "guest-get-fsinfo" ) ) ;
 goto cleanup ;
 }
 if ( VIR_STRDUP ( info_ret [ i ] -> name , virJSONValueObjectGetString ( entry , "name" ) ) < 0 ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "'name' missing in reply of guest-get-fsinfo" ) ) ;
 goto cleanup ;
 }
 if ( VIR_STRDUP ( info_ret [ i ] -> fstype , virJSONValueObjectGetString ( entry , "type" ) ) < 0 ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "'type' missing in reply of guest-get-fsinfo" ) ) ;
 goto cleanup ;
 }
 if ( ! ( entry = virJSONValueObjectGet ( entry , "disk" ) ) ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "'disk' missing in reply of guest-get-fsinfo" ) ) ;
 goto cleanup ;
 }
 if ( entry -> type != VIR_JSON_TYPE_ARRAY ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "guest-get-fsinfo 'disk' data was not an array" ) ) ;
 goto cleanup ;
 }
 ndisk = virJSONValueArraySize ( entry ) ;
 if ( ! ndisk ) continue ;
 if ( VIR_ALLOC_N ( info_ret [ i ] -> devAlias , ndisk ) < 0 ) goto cleanup ;
 alias = info_ret [ i ] -> devAlias ;
 info_ret [ i ] -> ndevAlias = 0 ;
 for ( j = 0 ;
 j < ndisk ;
 j ++ ) {
 virJSONValuePtr disk = virJSONValueArrayGet ( entry , j ) ;
 virJSONValuePtr pci ;
 int diskaddr [ 3 ] , pciaddr [ 4 ] ;
 const char * diskaddr_comp [ ] = {
 "bus" , "target" , "unit" }
 ;
 const char * pciaddr_comp [ ] = {
 "domain" , "bus" , "slot" , "function" }
 ;
 virDomainDiskDefPtr diskDef ;
 if ( ! disk ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "array element '%zd' of '%zd' missing in " "guest-get-fsinfo 'disk' data" ) , j , ndisk ) ;
 goto cleanup ;
 }
 if ( ! ( pci = virJSONValueObjectGet ( disk , "pci-controller" ) ) ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "'pci-controller' missing in guest-get-fsinfo " "'disk' data" ) ) ;
 goto cleanup ;
 }
 for ( k = 0 ;
 k < 3 ;
 k ++ ) {
 if ( virJSONValueObjectGetNumberInt ( disk , diskaddr_comp [ k ] , & diskaddr [ k ] ) < 0 ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "'%s' missing in guest-get-fsinfo " "'disk' data" ) , diskaddr_comp [ k ] ) ;
 goto cleanup ;
 }
 }
 for ( k = 0 ;
 k < 4 ;
 k ++ ) {
 if ( virJSONValueObjectGetNumberInt ( pci , pciaddr_comp [ k ] , & pciaddr [ k ] ) < 0 ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "'%s' missing in guest-get-fsinfo " "'pci-address' data" ) , pciaddr_comp [ k ] ) ;
 goto cleanup ;
 }
 }
 pci_address . domain = pciaddr [ 0 ] ;
 pci_address . bus = pciaddr [ 1 ] ;
 pci_address . slot = pciaddr [ 2 ] ;
 pci_address . function = pciaddr [ 3 ] ;
 if ( ! ( diskDef = virDomainDiskByAddress ( vmdef , & pci_address , diskaddr [ 0 ] , diskaddr [ 1 ] , diskaddr [ 2 ] ) ) ) continue ;
 if ( VIR_STRDUP ( * alias , diskDef -> dst ) < 0 ) goto cleanup ;
 if ( * alias ) {
 alias ++ ;
 info_ret [ i ] -> ndevAlias ++ ;
 }
 }
 }
 * info = info_ret ;
 info_ret = NULL ;
 ret = ndata ;
 cleanup : if ( info_ret ) {
 for ( i = 0 ;
 i < ndata ;
 i ++ ) virDomainFSInfoFree ( info_ret [ i ] ) ;
 VIR_FREE ( info_ret ) ;
 }
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }