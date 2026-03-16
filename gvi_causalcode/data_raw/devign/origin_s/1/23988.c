void qemu_ram_free(ram_addr_t addr)

{

    RAMBlock *block;



    QLIST_FOREACH(block, &ram_list.blocks, next) {

        if (addr == block->offset) {

            QLIST_REMOVE(block, next);

            if (block->flags & RAM_PREALLOC_MASK) {

                ;

            } else if (mem_path) {


                if (block->fd) {

                    munmap(block->host, block->length);

                    close(block->fd);

                } else {

                    qemu_vfree(block->host);

                }


            } else {


                munmap(block->host, block->length);


                qemu_vfree(block->host);


            }

            qemu_free(block);

            return;

        }

    }



}