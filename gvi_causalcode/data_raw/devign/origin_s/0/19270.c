static ssize_t rtl8139_do_receive(VLANClientState *nc, const uint8_t *buf, size_t size_, int do_interrupt)

{

    RTL8139State *s = DO_UPCAST(NICState, nc, nc)->opaque;

    int size = size_;



    uint32_t packet_header = 0;



    uint8_t buf1[60];

    static const uint8_t broadcast_macaddr[6] =

        { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };



    DEBUG_PRINT((">>> RTL8139: received len=%d\n", size));



     

    if (!s->clock_enabled)

    {

        DEBUG_PRINT(("RTL8139: stopped ==========================\n"));

        return -1;

    }



     



    if (!rtl8139_receiver_enabled(s))

    {

        DEBUG_PRINT(("RTL8139: receiver disabled ================\n"));

        return -1;

    }



     

    if (s->RxConfig & AcceptAllPhys) {

         

        DEBUG_PRINT((">>> RTL8139: packet received in promiscuous mode\n"));



    } else {

        if (!memcmp(buf,  broadcast_macaddr, 6)) {

             

            if (!(s->RxConfig & AcceptBroadcast))

            {

                DEBUG_PRINT((">>> RTL8139: broadcast packet rejected\n"));



                 

                ++s->tally_counters.RxERR;



                return size;

            }



            packet_header |= RxBroadcast;



            DEBUG_PRINT((">>> RTL8139: broadcast packet received\n"));



             

            ++s->tally_counters.RxOkBrd;



        } else if (buf[0] & 0x01) {

             

            if (!(s->RxConfig & AcceptMulticast))

            {

                DEBUG_PRINT((">>> RTL8139: multicast packet rejected\n"));



                 

                ++s->tally_counters.RxERR;



                return size;

            }



            int mcast_idx = compute_mcast_idx(buf);



            if (!(s->mult[mcast_idx >> 3] & (1 << (mcast_idx & 7))))

            {

                DEBUG_PRINT((">>> RTL8139: multicast address mismatch\n"));



                 

                ++s->tally_counters.RxERR;



                return size;

            }



            packet_header |= RxMulticast;



            DEBUG_PRINT((">>> RTL8139: multicast packet received\n"));



             

            ++s->tally_counters.RxOkMul;



        } else if (s->phys[0] == buf[0] &&

                   s->phys[1] == buf[1] &&

                   s->phys[2] == buf[2] &&

                   s->phys[3] == buf[3] &&

                   s->phys[4] == buf[4] &&

                   s->phys[5] == buf[5]) {

             

            if (!(s->RxConfig & AcceptMyPhys))

            {

                DEBUG_PRINT((">>> RTL8139: rejecting physical address matching packet\n"));



                 

                ++s->tally_counters.RxERR;



                return size;

            }



            packet_header |= RxPhysical;



            DEBUG_PRINT((">>> RTL8139: physical address matching packet received\n"));



             

            ++s->tally_counters.RxOkPhy;



        } else {



            DEBUG_PRINT((">>> RTL8139: unknown packet\n"));



             

            ++s->tally_counters.RxERR;



            return size;

        }

    }



     

    if (size < MIN_BUF_SIZE) {

        memcpy(buf1, buf, size);

        memset(buf1 + size, 0, MIN_BUF_SIZE - size);

        buf = buf1;

        size = MIN_BUF_SIZE;

    }



    if (rtl8139_cp_receiver_enabled(s))

    {

        DEBUG_PRINT(("RTL8139: in C+ Rx mode ================\n"));






 

 



        int descriptor = s->currCPlusRxDesc;

        target_phys_addr_t cplus_rx_ring_desc;



        cplus_rx_ring_desc = rtl8139_addr64(s->RxRingAddrLO, s->RxRingAddrHI);

        cplus_rx_ring_desc += 16 * descriptor;



        DEBUG_PRINT(("RTL8139: +++ C+ mode reading RX descriptor %d from host memory at %08x %08x = %016" PRIx64 "\n",

               descriptor, s->RxRingAddrHI, s->RxRingAddrLO, (uint64_t)cplus_rx_ring_desc));



        uint32_t val, rxdw0,rxdw1,rxbufLO,rxbufHI;



        cpu_physical_memory_read(cplus_rx_ring_desc,    (uint8_t *)&val, 4);

        rxdw0 = le32_to_cpu(val);

        cpu_physical_memory_read(cplus_rx_ring_desc+4,  (uint8_t *)&val, 4);

        rxdw1 = le32_to_cpu(val);

        cpu_physical_memory_read(cplus_rx_ring_desc+8,  (uint8_t *)&val, 4);

        rxbufLO = le32_to_cpu(val);

        cpu_physical_memory_read(cplus_rx_ring_desc+12, (uint8_t *)&val, 4);

        rxbufHI = le32_to_cpu(val);



        DEBUG_PRINT(("RTL8139: +++ C+ mode RX descriptor %d %08x %08x %08x %08x\n",

               descriptor,

               rxdw0, rxdw1, rxbufLO, rxbufHI));



        if (!(rxdw0 & CP_RX_OWN))

        {

            DEBUG_PRINT(("RTL8139: C+ Rx mode : descriptor %d is owned by host\n", descriptor));



            s->IntrStatus |= RxOverflow;

            ++s->RxMissed;



             

            ++s->tally_counters.RxERR;

            ++s->tally_counters.MissPkt;



            rtl8139_update_irq(s);

            return size_;

        }



        uint32_t rx_space = rxdw0 & CP_RX_BUFFER_SIZE_MASK;



         



        if (size+4 > rx_space)

        {

            DEBUG_PRINT(("RTL8139: C+ Rx mode : descriptor %d size %d received %d + 4\n",

                   descriptor, rx_space, size));



            s->IntrStatus |= RxOverflow;

            ++s->RxMissed;



             

            ++s->tally_counters.RxERR;

            ++s->tally_counters.MissPkt;



            rtl8139_update_irq(s);

            return size_;

        }



        target_phys_addr_t rx_addr = rtl8139_addr64(rxbufLO, rxbufHI);



         

        cpu_physical_memory_write( rx_addr, buf, size );



        if (s->CpCmd & CPlusRxChkSum)

        {

             

        }


        val = cpu_to_le32(crc32(0, buf, size));


        val = 0;


        cpu_physical_memory_write( rx_addr+size, (uint8_t *)&val, 4);













         

        rxdw0 &= ~CP_RX_OWN;



         

        rxdw0 |= CP_RX_STATUS_FS;



         

        rxdw0 |= CP_RX_STATUS_LS;



         

        if (packet_header & RxBroadcast)

            rxdw0 |= CP_RX_STATUS_BAR;

        if (packet_header & RxMulticast)

            rxdw0 |= CP_RX_STATUS_MAR;

        if (packet_header & RxPhysical)

            rxdw0 |= CP_RX_STATUS_PAM;



         

        rxdw0 &= ~CP_RX_BUFFER_SIZE_MASK;

        rxdw0 |= (size+4);



         

        rxdw1 &= ~CP_RX_TAVA;



         

        val = cpu_to_le32(rxdw0);

        cpu_physical_memory_write(cplus_rx_ring_desc,    (uint8_t *)&val, 4);

        val = cpu_to_le32(rxdw1);

        cpu_physical_memory_write(cplus_rx_ring_desc+4,  (uint8_t *)&val, 4);



         

        ++s->tally_counters.RxOk;



         

        if (rxdw0 & CP_RX_EOR)

        {

            s->currCPlusRxDesc = 0;

        }

        else

        {

            ++s->currCPlusRxDesc;

        }



        DEBUG_PRINT(("RTL8139: done C+ Rx mode ----------------\n"));



    }

    else

    {

        DEBUG_PRINT(("RTL8139: in ring Rx mode ================\n"));



         

        int avail = MOD2(s->RxBufferSize + s->RxBufPtr - s->RxBufAddr, s->RxBufferSize);



         



        if (avail != 0 && size + 8 >= avail)

        {

            DEBUG_PRINT(("rx overflow: rx buffer length %d head 0x%04x read 0x%04x === available 0x%04x need 0x%04x\n",

                   s->RxBufferSize, s->RxBufAddr, s->RxBufPtr, avail, size + 8));



            s->IntrStatus |= RxOverflow;

            ++s->RxMissed;

            rtl8139_update_irq(s);

            return size_;

        }



        packet_header |= RxStatusOK;



        packet_header |= (((size+4) << 16) & 0xffff0000);



         

        uint32_t val = cpu_to_le32(packet_header);



        rtl8139_write_buffer(s, (uint8_t *)&val, 4);



        rtl8139_write_buffer(s, buf, size);


        val = cpu_to_le32(crc32(0, buf, size));


        val = 0;




        rtl8139_write_buffer(s, (uint8_t *)&val, 4);



         

        s->RxBufAddr = MOD2((s->RxBufAddr + 3) & ~0x3, s->RxBufferSize);



         



        DEBUG_PRINT(("   received: rx buffer length %d head 0x%04x read 0x%04x\n",

               s->RxBufferSize, s->RxBufAddr, s->RxBufPtr));

    }



    s->IntrStatus |= RxOK;



    if (do_interrupt)

    {

        rtl8139_update_irq(s);

    }



    return size_;

}
