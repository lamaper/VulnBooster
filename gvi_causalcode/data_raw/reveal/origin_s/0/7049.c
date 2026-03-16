static __inline__ __u64 ethtool_get_flow_spec_ring_vf ( __u64 ring_cookie ) {
 return ( ETHTOOL_RX_FLOW_SPEC_RING_VF & ring_cookie ) >> ETHTOOL_RX_FLOW_SPEC_RING_VF_OFF ;
 }