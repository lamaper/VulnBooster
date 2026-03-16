int qemuAssignDeviceAliases ( virDomainDefPtr def , virQEMUCapsPtr qemuCaps ) {
 size_t i ;
 for ( i = 0 ;
 i < def -> ndisks ;
 i ++ ) {
 if ( qemuAssignDeviceDiskAlias ( def , def -> disks [ i ] , qemuCaps ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nnets ;
 i ++ ) {
 if ( qemuAssignDeviceNetAlias ( def , def -> nets [ i ] , - 1 ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nfss ;
 i ++ ) {
 if ( virAsprintf ( & def -> fss [ i ] -> info . alias , "fs%zu" , i ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nsounds ;
 i ++ ) {
 if ( virAsprintf ( & def -> sounds [ i ] -> info . alias , "sound%zu" , i ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nhostdevs ;
 i ++ ) {
 if ( ! def -> hostdevs [ i ] -> info -> alias && qemuAssignDeviceHostdevAlias ( def , & def -> hostdevs [ i ] -> info -> alias , - 1 ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nredirdevs ;
 i ++ ) {
 if ( qemuAssignDeviceRedirdevAlias ( def , def -> redirdevs [ i ] , i ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nvideos ;
 i ++ ) {
 if ( virAsprintf ( & def -> videos [ i ] -> info . alias , "video%zu" , i ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> ncontrollers ;
 i ++ ) {
 if ( qemuAssignDeviceControllerAlias ( def , qemuCaps , def -> controllers [ i ] ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> ninputs ;
 i ++ ) {
 if ( virAsprintf ( & def -> inputs [ i ] -> info . alias , "input%zu" , i ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nparallels ;
 i ++ ) {
 if ( qemuAssignDeviceChrAlias ( def , def -> parallels [ i ] , i ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nserials ;
 i ++ ) {
 if ( qemuAssignDeviceChrAlias ( def , def -> serials [ i ] , i ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nchannels ;
 i ++ ) {
 if ( qemuAssignDeviceChrAlias ( def , def -> channels [ i ] , i ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nconsoles ;
 i ++ ) {
 if ( qemuAssignDeviceChrAlias ( def , def -> consoles [ i ] , i ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nhubs ;
 i ++ ) {
 if ( virAsprintf ( & def -> hubs [ i ] -> info . alias , "hub%zu" , i ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nshmems ;
 i ++ ) {
 if ( virAsprintf ( & def -> shmems [ i ] -> info . alias , "shmem%zu" , i ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nsmartcards ;
 i ++ ) {
 if ( virAsprintf ( & def -> smartcards [ i ] -> info . alias , "smartcard%zu" , i ) < 0 ) return - 1 ;
 }
 if ( def -> watchdog ) {
 if ( virAsprintf ( & def -> watchdog -> info . alias , "watchdog%d" , 0 ) < 0 ) return - 1 ;
 }
 if ( def -> memballoon ) {
 if ( virAsprintf ( & def -> memballoon -> info . alias , "balloon%d" , 0 ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nrngs ;
 i ++ ) {
 if ( virAsprintf ( & def -> rngs [ i ] -> info . alias , "rng%zu" , i ) < 0 ) return - 1 ;
 }
 if ( def -> tpm ) {
 if ( virAsprintf ( & def -> tpm -> info . alias , "tpm%d" , 0 ) < 0 ) return - 1 ;
 }
 for ( i = 0 ;
 i < def -> nmems ;
 i ++ ) {
 if ( virAsprintf ( & def -> mems [ i ] -> info . alias , "dimm%zu" , i ) < 0 ) return - 1 ;
 }
 return 0 ;
 }