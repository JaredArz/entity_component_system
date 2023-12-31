#include "component_array.h"
#include "entity_manager.h"
#include "component_manager.h"
#include <iostream>
#include <stdio.h>

typedef struct{
    int x,y,z;

} Vec3;

typedef struct{
    Vec3 position;
} trans_t;


int main(void){

    ecs::entity_t ea,eb,ec;

    e_mgr::entity_manager mgr;
    mgr   = e_mgr::entity_manager();

    ecs::signature_t sa = 0x11;
    ea = mgr.create_entity();
    mgr.set_signature(ea,sa);
    eb = mgr.create_entity();
    ec = mgr.create_entity();


    printf("Id of entity a: %d\n", ea);
    printf("Signature of entity a: %d\n",mgr.get_signature(ea));
    printf("Id of entity b: %d\n", eb);
    printf("Id of entity c: %d\n", ec);

    return 0;
}
