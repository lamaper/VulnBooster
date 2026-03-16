static void ppc_cpu_class_init(ObjectClass *oc, void *data)

{

    PowerPCCPUClass *pcc = POWERPC_CPU_CLASS(oc);

    CPUClass *cc = CPU_CLASS(oc);

    DeviceClass *dc = DEVICE_CLASS(oc);



    pcc->parent_realize = dc->realize;

    pcc->pvr = CPU_POWERPC_DEFAULT_MASK;

    pcc->pvr_mask = CPU_POWERPC_DEFAULT_MASK;

    pcc->interrupts_big_endian = ppc_cpu_interrupts_big_endian_always;

    dc->realize = ppc_cpu_realizefn;

    dc->unrealize = ppc_cpu_unrealizefn;



    pcc->parent_reset = cc->reset;

    cc->reset = ppc_cpu_reset;



    cc->class_by_name = ppc_cpu_class_by_name;

    cc->has_work = ppc_cpu_has_work;

    cc->do_interrupt = ppc_cpu_do_interrupt;

    cc->dump_state = ppc_cpu_dump_state;

    cc->dump_statistics = ppc_cpu_dump_statistics;

    cc->set_pc = ppc_cpu_set_pc;

    cc->gdb_read_register = ppc_cpu_gdb_read_register;

    cc->gdb_write_register = ppc_cpu_gdb_write_register;


    cc->handle_mmu_fault = ppc_cpu_handle_mmu_fault;


    cc->get_phys_page_debug = ppc_cpu_get_phys_page_debug;

    cc->vmsd = &vmstate_ppc_cpu;


    cc->write_elf64_note = ppc64_cpu_write_elf64_note;

    cc->write_elf64_qemunote = ppc64_cpu_write_elf64_qemunote;





    cc->gdb_num_core_regs = 71;


    cc->gdb_read_register = ppc_cpu_gdb_read_register_apple;

    cc->gdb_write_register = ppc_cpu_gdb_write_register_apple;

    cc->gdb_num_core_regs = 71 + 32;



    cc->gdb_core_xml_file = "power64-core.xml";


    cc->gdb_core_xml_file = "power-core.xml";



    cc->virtio_is_big_endian = ppc_cpu_is_big_endian;




    dc->fw_name = "PowerPC,UNKNOWN";

}
