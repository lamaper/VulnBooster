void net_rx_pkt_dump(struct NetRxPkt *pkt)

{


    assert(pkt);



    printf("RX PKT: tot_len: %d, vlan_stripped: %d, vlan_tag: %d\n",

              pkt->tot_len, pkt->vlan_stripped, pkt->tci);


}
