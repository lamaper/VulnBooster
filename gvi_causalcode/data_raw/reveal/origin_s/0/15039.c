IN_PROC_BROWSER_TEST_F ( BluetoothChooserBrowserTest , InvokeDialog_ConnectedBubble ) {
 set_status ( FakeBluetoothChooserController : : BluetoothStatus : : IDLE ) ;
 AddConnectedDevice ( ) ;
 RunDialog ( ) ;
 }