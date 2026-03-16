IN_PROC_BROWSER_TEST_F ( BluetoothChooserBrowserTest , InvokeDialog_ScanningModal ) {
 set_status ( FakeBluetoothChooserController : : BluetoothStatus : : SCANNING ) ;
 RunDialog ( ) ;
 }