IN_PROC_BROWSER_TEST_F ( BluetoothChooserBrowserTest , InvokeDialog_NoDevicesBubble ) {
 set_status ( FakeBluetoothChooserController : : BluetoothStatus : : IDLE ) ;
 RunDialog ( ) ;
 }