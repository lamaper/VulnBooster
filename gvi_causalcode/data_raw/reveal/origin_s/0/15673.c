VirtIODevice * virtio_net_init ( DeviceState * dev , NICConf * conf , virtio_net_conf * net ) {
 VirtIONet * n ;
 n = ( VirtIONet * ) virtio_common_init ( "virtio-net" , VIRTIO_ID_NET , sizeof ( struct virtio_net_config ) , sizeof ( VirtIONet ) ) ;
 n -> vdev . get_config = virtio_net_get_config ;
 n -> vdev . set_config = virtio_net_set_config ;
 n -> vdev . get_features = virtio_net_get_features ;
 n -> vdev . set_features = virtio_net_set_features ;
 n -> vdev . bad_features = virtio_net_bad_features ;
 n -> vdev . reset = virtio_net_reset ;
 n -> vdev . set_status = virtio_net_set_status ;
 n -> rx_vq = virtio_add_queue ( & n -> vdev , 256 , virtio_net_handle_rx ) ;
 if ( net -> tx && strcmp ( net -> tx , "timer" ) && strcmp ( net -> tx , "bh" ) ) {
 error_report ( "virtio-net: " "Unknown option tx=%s, valid options: \"timer\" \"bh\"" , net -> tx ) ;
 error_report ( "Defaulting to \"bh\"" ) ;
 }
 if ( net -> tx && ! strcmp ( net -> tx , "timer" ) ) {
 n -> tx_vq = virtio_add_queue ( & n -> vdev , 256 , virtio_net_handle_tx_timer ) ;
 n -> tx_timer = qemu_new_timer_ns ( vm_clock , virtio_net_tx_timer , n ) ;
 n -> tx_timeout = net -> txtimer ;
 }
 else {
 n -> tx_vq = virtio_add_queue ( & n -> vdev , 256 , virtio_net_handle_tx_bh ) ;
 n -> tx_bh = qemu_bh_new ( virtio_net_tx_bh , n ) ;
 }
 n -> ctrl_vq = virtio_add_queue ( & n -> vdev , 64 , virtio_net_handle_ctrl ) ;
 qemu_macaddr_default_if_unset ( & conf -> macaddr ) ;
 memcpy ( & n -> mac [ 0 ] , & conf -> macaddr , sizeof ( n -> mac ) ) ;
 n -> status = VIRTIO_NET_S_LINK_UP ;
 n -> nic = qemu_new_nic ( & net_virtio_info , conf , object_get_typename ( OBJECT ( dev ) ) , dev -> id , n ) ;
 qemu_format_nic_info_str ( & n -> nic -> nc , conf -> macaddr . a ) ;
 n -> tx_waiting = 0 ;
 n -> tx_burst = net -> txburst ;
 n -> mergeable_rx_bufs = 0 ;
 n -> promisc = 1 ;
 n -> mac_table . macs = g_malloc0 ( MAC_TABLE_ENTRIES * ETH_ALEN ) ;
 n -> vlans = g_malloc0 ( MAX_VLAN >> 3 ) ;
 n -> qdev = dev ;
 register_savevm ( dev , "virtio-net" , - 1 , VIRTIO_NET_VM_VERSION , virtio_net_save , virtio_net_load , n ) ;
 add_boot_device_path ( conf -> bootindex , dev , "/ethernet-phy@0" ) ;
 return & n -> vdev ;
 }