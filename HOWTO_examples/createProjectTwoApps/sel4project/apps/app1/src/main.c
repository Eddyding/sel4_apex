#include <autoconf.h>

#include <stdio.h>
#include <assert.h>

#include <sel4/sel4.h>

#include <simple/simple.h>
#include <simple-default/simple-default.h>
#include <sel4debug/debug.h>

#include <vka/object.h>

#include <allocman/allocman.h>
#include <allocman/bootstrap.h>
#include <allocman/vka.h>

#include <vspace/vspace.h>

#include <sel4utils/vspace.h>
#include <sel4utils/mapping.h>
#include <sel4utils/process.h>

#define APP_PRIORITY seL4_MaxPrio
#define APP_IMAGE_NAME "app2"

char _cpio_archive[1];

#define ALLOCATOR_STATIC_POOL_SIZE ((1 << seL4_PageBits) * 10)
UNUSED static char allocator_mem_pool[ALLOCATOR_STATIC_POOL_SIZE];

#define ALLOCATOR_VIRTUAL_POOL_SIZE ((1 << seL4_PageBits) * 100)

UNUSED static sel4utils_alloc_data_t data;

#define THREAD_2_STACK_SIZE 4096
UNUSED static int thread_2_stack[THREAD_2_STACK_SIZE];

seL4_BootInfo *info;
simple_t simple;
vka_t vka;
vspace_t vspace;
allocman_t *allocman;

int main(int argc, char *argv[]) {
    UNUSED int error;
    
    info = seL4_GetBootInfo();
    
    simple_default_init_bootinfo(&simple, info);

    allocman = bootstrap_use_current_simple(&simple, ALLOCATOR_STATIC_POOL_SIZE, allocator_mem_pool);

    allocman_make_vka(&vka, allocman);

    sel4utils_bootstrap_vspace_with_bootinfo_leaky(&vspace, &data, simple_get_pd(&simple), &vka, info);
    
    void *vaddr;
    UNUSED reservation_t virtual_reservation;
    virtual_reservation = vspace_reserve_range(&vspace, ALLOCATOR_VIRTUAL_POOL_SIZE, seL4_AllRights, 1, &vaddr);
    bootstrap_configure_virtual_pool(allocman, vaddr, ALLOCATOR_VIRTUAL_POOL_SIZE, simple_get_pd(&simple));

    sel4utils_process_t new_process;
    error = sel4utils_configure_process(&new_process, &vka, &vspace, APP_PRIORITY, APP_IMAGE_NAME);
    printf("app1: error1: %d\n", error);

    error = sel4utils_spawn_process_v(&new_process, &vka, &vspace, 0, NULL, 1);
    printf("app1: error2: %d\n", error);
    
    printf("Hello World! from app1\n");

    return 0;
}


