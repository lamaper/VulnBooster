IN_PROC_BROWSER_TEST_F ( BluetoothChooserBrowserTest , InvokeDialog_ScanningWithDevicesModal ) {
 set_status ( FakeBluetoothChooserController : : BluetoothStatus : : SCANNING ) ;
 AddDeviceForAllStrengths ( ) ;
 RunDialog ( ) ;
 }