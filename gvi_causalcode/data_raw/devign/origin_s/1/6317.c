static int rtl8139_cplus_transmit_one(RTL8139State *s)

{

    if (!rtl8139_transmitter_enabled(s))

    {

        DPRINTF("+++ C+ mode: transmitter disabled\n");

        return 0;

    }



    if (!rtl8139_cp_transmitter_enabled(s))

    {

        DPRINTF("+++ C+ mode: C+ transmitter disabled\n");

        return 0 ;

    }



    int descriptor = s->currCPlusTxDesc;



    dma_addr_t cplus_tx_ring_desc = rtl8139_addr64(s->TxAddr[0], s->TxAddr[1]);



     

    cplus_tx_ring_desc += 16 * descriptor;



    DPRINTF("+++ C+ mode reading TX descriptor %d from host memory at "

        "%08x %08x = 0x"DMA_ADDR_FMT"\n", descriptor, s->TxAddr[1],

        s->TxAddr[0], cplus_tx_ring_desc);



    uint32_t val, txdw0,txdw1,txbufLO,txbufHI;



    pci_dma_read(&s->dev, cplus_tx_ring_desc,    (uint8_t *)&val, 4);

    txdw0 = le32_to_cpu(val);

    pci_dma_read(&s->dev, cplus_tx_ring_desc+4,  (uint8_t *)&val, 4);

    txdw1 = le32_to_cpu(val);

    pci_dma_read(&s->dev, cplus_tx_ring_desc+8,  (uint8_t *)&val, 4);

    txbufLO = le32_to_cpu(val);

    pci_dma_read(&s->dev, cplus_tx_ring_desc+12, (uint8_t *)&val, 4);

    txbufHI = le32_to_cpu(val);



    DPRINTF("+++ C+ mode TX descriptor %d %08x %08x %08x %08x\n", descriptor,

        txdw0, txdw1, txbufLO, txbufHI);





















    if (!(txdw0 & CP_TX_OWN))

    {

        DPRINTF("C+ Tx mode : descriptor %d is owned by host\n", descriptor);

        return 0 ;

    }



    DPRINTF("+++ C+ Tx mode : transmitting from descriptor %d\n", descriptor);



    if (txdw0 & CP_TX_FS)

    {

        DPRINTF("+++ C+ Tx mode : descriptor %d is first segment "

            "descriptor\n", descriptor);



         

        s->cplus_txbuffer_offset = 0;

    }



    int txsize = txdw0 & CP_TX_BUFFER_SIZE_MASK;

    dma_addr_t tx_addr = rtl8139_addr64(txbufLO, txbufHI);



     

    if (!s->cplus_txbuffer)

    {

        s->cplus_txbuffer_len = CP_TX_BUFFER_SIZE;

        s->cplus_txbuffer = g_malloc(s->cplus_txbuffer_len);

        s->cplus_txbuffer_offset = 0;



        DPRINTF("+++ C+ mode transmission buffer allocated space %d\n",

            s->cplus_txbuffer_len);

    }



    while (s->cplus_txbuffer && s->cplus_txbuffer_offset + txsize >= s->cplus_txbuffer_len)

    {

        s->cplus_txbuffer_len += CP_TX_BUFFER_SIZE;

        s->cplus_txbuffer = g_realloc(s->cplus_txbuffer, s->cplus_txbuffer_len);



        DPRINTF("+++ C+ mode transmission buffer space changed to %d\n",

            s->cplus_txbuffer_len);

    }



    if (!s->cplus_txbuffer)

    {

         



        DPRINTF("+++ C+ mode transmiter failed to reallocate %d bytes\n",

            s->cplus_txbuffer_len);



         

        ++s->tally_counters.TxERR;

        ++s->tally_counters.TxAbt;



        return 0;

    }



     



    DPRINTF("+++ C+ mode transmit reading %d bytes from host memory at "

            DMA_ADDR_FMT" to offset %d\n", txsize, tx_addr,

            s->cplus_txbuffer_offset);



    pci_dma_read(&s->dev, tx_addr,

                 s->cplus_txbuffer + s->cplus_txbuffer_offset, txsize);

    s->cplus_txbuffer_offset += txsize;



     

    if (txdw0 & CP_TX_EOR)

    {

        s->currCPlusTxDesc = 0;

    }

    else

    {

        ++s->currCPlusTxDesc;

        if (s->currCPlusTxDesc >= 64)

            s->currCPlusTxDesc = 0;

    }



     

    txdw0 &= ~CP_RX_OWN;



     

    txdw0 &= ~CP_TX_STATUS_UNF;

    txdw0 &= ~CP_TX_STATUS_TES;

    txdw0 &= ~CP_TX_STATUS_OWC;

    txdw0 &= ~CP_TX_STATUS_LNKF;

    txdw0 &= ~CP_TX_STATUS_EXC;



     

    val = cpu_to_le32(txdw0);

    pci_dma_write(&s->dev, cplus_tx_ring_desc, (uint8_t *)&val, 4);



     

    if (txdw0 & CP_TX_LS)

    {

        uint8_t dot1q_buffer_space[VLAN_HLEN];

        uint16_t *dot1q_buffer;



        DPRINTF("+++ C+ Tx mode : descriptor %d is last segment descriptor\n",

            descriptor);



         



        uint8_t *saved_buffer  = s->cplus_txbuffer;

        int      saved_size    = s->cplus_txbuffer_offset;

        int      saved_buffer_len = s->cplus_txbuffer_len;



         

        if (txdw1 & CP_TX_TAGC) {

             

            DPRINTF("+++ C+ Tx mode : inserting vlan tag with ""tci: %u\n",

                bswap16(txdw1 & CP_TX_VLAN_TAG_MASK));



            dot1q_buffer = (uint16_t *) dot1q_buffer_space;

            dot1q_buffer[0] = cpu_to_be16(ETH_P_8021Q);

             

            dot1q_buffer[1] = cpu_to_le16(txdw1 & CP_TX_VLAN_TAG_MASK);

        } else {

            dot1q_buffer = NULL;

        }



         

        s->cplus_txbuffer = NULL;

        s->cplus_txbuffer_offset = 0;

        s->cplus_txbuffer_len = 0;



        if (txdw0 & (CP_TX_IPCS | CP_TX_UDPCS | CP_TX_TCPCS | CP_TX_LGSEN))

        {

            DPRINTF("+++ C+ mode offloaded task checksum\n");



             

            ip_header *ip = NULL;

            int hlen = 0;

            uint8_t  ip_protocol = 0;

            uint16_t ip_data_len = 0;



            uint8_t *eth_payload_data = NULL;

            size_t   eth_payload_len  = 0;



            int proto = be16_to_cpu(*(uint16_t *)(saved_buffer + 12));

            if (proto == ETH_P_IP)

            {

                DPRINTF("+++ C+ mode has IP packet\n");



                 

                eth_payload_data = saved_buffer + ETH_HLEN;

                eth_payload_len  = saved_size   - ETH_HLEN;



                ip = (ip_header*)eth_payload_data;



                if (IP_HEADER_VERSION(ip) != IP_HEADER_VERSION_4) {

                    DPRINTF("+++ C+ mode packet has bad IP version %d "

                        "expected %d\n", IP_HEADER_VERSION(ip),

                        IP_HEADER_VERSION_4);

                    ip = NULL;

                } else {

                    hlen = IP_HEADER_LENGTH(ip);

                    ip_protocol = ip->ip_p;

                    ip_data_len = be16_to_cpu(ip->ip_len) - hlen;

                }

            }



            if (ip)

            {

                if (txdw0 & CP_TX_IPCS)

                {

                    DPRINTF("+++ C+ mode need IP checksum\n");



                    if (hlen<sizeof(ip_header) || hlen>eth_payload_len) { 

                         

                         

                    }

                    else

                    {

                        ip->ip_sum = 0;

                        ip->ip_sum = ip_checksum(ip, hlen);

                        DPRINTF("+++ C+ mode IP header len=%d checksum=%04x\n",

                            hlen, ip->ip_sum);

                    }

                }



                if ((txdw0 & CP_TX_LGSEN) && ip_protocol == IP_PROTO_TCP)

                {

                    int large_send_mss = (txdw0 >> 16) & CP_TC_LGSEN_MSS_MASK;



                    DPRINTF("+++ C+ mode offloaded task TSO MTU=%d IP data %d "

                        "frame data %d specified MSS=%d\n", ETH_MTU,

                        ip_data_len, saved_size - ETH_HLEN, large_send_mss);



                    int tcp_send_offset = 0;

                    int send_count = 0;



                     

                    uint8_t saved_ip_header[60];



                     

                    memcpy(saved_ip_header, eth_payload_data, hlen);



                     

                    uint8_t *data_to_checksum     = eth_payload_data + hlen - 12;

                     



                     

                    tcp_header *p_tcp_hdr = (tcp_header*)(eth_payload_data + hlen);



                    int tcp_hlen = TCP_HEADER_DATA_OFFSET(p_tcp_hdr);



                     

                    int tcp_data_len = ip_data_len - tcp_hlen;

                    int tcp_chunk_size = ETH_MTU - hlen - tcp_hlen;



                    DPRINTF("+++ C+ mode TSO IP data len %d TCP hlen %d TCP "

                        "data len %d TCP chunk size %d\n", ip_data_len,

                        tcp_hlen, tcp_data_len, tcp_chunk_size);



                     



                    int is_last_frame = 0;



                    for (tcp_send_offset = 0; tcp_send_offset < tcp_data_len; tcp_send_offset += tcp_chunk_size)

                    {

                        uint16_t chunk_size = tcp_chunk_size;



                         

                        if (tcp_send_offset + tcp_chunk_size >= tcp_data_len)

                        {

                            is_last_frame = 1;

                            chunk_size = tcp_data_len - tcp_send_offset;

                        }



                        DPRINTF("+++ C+ mode TSO TCP seqno %08x\n",

                            be32_to_cpu(p_tcp_hdr->th_seq));



                         

                         

                        memcpy(data_to_checksum, saved_ip_header + 12, 8);



                        DPRINTF("+++ C+ mode TSO calculating TCP checksum for "

                            "packet with %d bytes data\n", tcp_hlen +

                            chunk_size);



                        if (tcp_send_offset)

                        {

                            memcpy((uint8_t*)p_tcp_hdr + tcp_hlen, (uint8_t*)p_tcp_hdr + tcp_hlen + tcp_send_offset, chunk_size);

                        }



                         

                        if (!is_last_frame)

                        {

                            TCP_HEADER_CLEAR_FLAGS(p_tcp_hdr, TCP_FLAG_PUSH|TCP_FLAG_FIN);

                        }



                         

                        ip_pseudo_header *p_tcpip_hdr = (ip_pseudo_header *)data_to_checksum;

                        p_tcpip_hdr->zeros      = 0;

                        p_tcpip_hdr->ip_proto   = IP_PROTO_TCP;

                        p_tcpip_hdr->ip_payload = cpu_to_be16(tcp_hlen + chunk_size);



                        p_tcp_hdr->th_sum = 0;



                        int tcp_checksum = ip_checksum(data_to_checksum, tcp_hlen + chunk_size + 12);

                        DPRINTF("+++ C+ mode TSO TCP checksum %04x\n",

                            tcp_checksum);



                        p_tcp_hdr->th_sum = tcp_checksum;



                         

                        memcpy(eth_payload_data, saved_ip_header, hlen);



                         

                        ip->ip_len = cpu_to_be16(hlen + tcp_hlen + chunk_size);



                         

                        ip->ip_id = cpu_to_be16(tcp_send_offset/tcp_chunk_size + be16_to_cpu(ip->ip_id));



                        ip->ip_sum = 0;

                        ip->ip_sum = ip_checksum(eth_payload_data, hlen);

                        DPRINTF("+++ C+ mode TSO IP header len=%d "

                            "checksum=%04x\n", hlen, ip->ip_sum);



                        int tso_send_size = ETH_HLEN + hlen + tcp_hlen + chunk_size;

                        DPRINTF("+++ C+ mode TSO transferring packet size "

                            "%d\n", tso_send_size);

                        rtl8139_transfer_frame(s, saved_buffer, tso_send_size,

                            0, (uint8_t *) dot1q_buffer);



                         

                        p_tcp_hdr->th_seq = cpu_to_be32(chunk_size + be32_to_cpu(p_tcp_hdr->th_seq));

                        ++send_count;

                    }



                     

                    saved_size = 0;

                }

                else if (txdw0 & (CP_TX_TCPCS|CP_TX_UDPCS))

                {

                    DPRINTF("+++ C+ mode need TCP or UDP checksum\n");



                     

                    uint8_t saved_ip_header[60];

                    memcpy(saved_ip_header, eth_payload_data, hlen);



                    uint8_t *data_to_checksum     = eth_payload_data + hlen - 12;

                     



                     

                     

                    memcpy(data_to_checksum, saved_ip_header + 12, 8);



                    if ((txdw0 & CP_TX_TCPCS) && ip_protocol == IP_PROTO_TCP)

                    {

                        DPRINTF("+++ C+ mode calculating TCP checksum for "

                            "packet with %d bytes data\n", ip_data_len);



                        ip_pseudo_header *p_tcpip_hdr = (ip_pseudo_header *)data_to_checksum;

                        p_tcpip_hdr->zeros      = 0;

                        p_tcpip_hdr->ip_proto   = IP_PROTO_TCP;

                        p_tcpip_hdr->ip_payload = cpu_to_be16(ip_data_len);



                        tcp_header* p_tcp_hdr = (tcp_header *) (data_to_checksum+12);



                        p_tcp_hdr->th_sum = 0;



                        int tcp_checksum = ip_checksum(data_to_checksum, ip_data_len + 12);

                        DPRINTF("+++ C+ mode TCP checksum %04x\n",

                            tcp_checksum);



                        p_tcp_hdr->th_sum = tcp_checksum;

                    }

                    else if ((txdw0 & CP_TX_UDPCS) && ip_protocol == IP_PROTO_UDP)

                    {

                        DPRINTF("+++ C+ mode calculating UDP checksum for "

                            "packet with %d bytes data\n", ip_data_len);



                        ip_pseudo_header *p_udpip_hdr = (ip_pseudo_header *)data_to_checksum;

                        p_udpip_hdr->zeros      = 0;

                        p_udpip_hdr->ip_proto   = IP_PROTO_UDP;

                        p_udpip_hdr->ip_payload = cpu_to_be16(ip_data_len);



                        udp_header *p_udp_hdr = (udp_header *) (data_to_checksum+12);



                        p_udp_hdr->uh_sum = 0;



                        int udp_checksum = ip_checksum(data_to_checksum, ip_data_len + 12);

                        DPRINTF("+++ C+ mode UDP checksum %04x\n",

                            udp_checksum);



                        p_udp_hdr->uh_sum = udp_checksum;

                    }



                     

                    memcpy(eth_payload_data, saved_ip_header, hlen);

                }

            }

        }



         

        ++s->tally_counters.TxOk;



        DPRINTF("+++ C+ mode transmitting %d bytes packet\n", saved_size);



        rtl8139_transfer_frame(s, saved_buffer, saved_size, 1,

            (uint8_t *) dot1q_buffer);



         

        if (!s->cplus_txbuffer)

        {

            s->cplus_txbuffer        = saved_buffer;

            s->cplus_txbuffer_len    = saved_buffer_len;

            s->cplus_txbuffer_offset = 0;

        }

        else

        {

            g_free(saved_buffer);

        }

    }

    else

    {

        DPRINTF("+++ C+ mode transmission continue to next descriptor\n");

    }



    return 1;

}
