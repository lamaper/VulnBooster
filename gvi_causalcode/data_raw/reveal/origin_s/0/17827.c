IN_PROC_BROWSER_TEST_F ( BluetoothChooserBrowserTest , InvokeDialog_ScanningBubble ) {
 set_status ( FakeBluetoothChooserController : : BluetoothStatus : : SCANNING ) ;
 RunDialog ( ) ;
 }