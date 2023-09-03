#include "entity_manager.h"
#include <iostream>

int main(void){

    int id;
    int id1;
    int id2;
    e_mgr::entity_manager m;
    m = e_mgr::entity_manager();
    id = m.create_entity();
    id1 = m.create_entity();
    id2 = m.create_entity();
    std::cout << id << std::endl;
    std::cout << id1 << std::endl;
    std::cout << id2 << std::endl;

    size_t msize;
    msize = 10;
    std::cout << msize << std::endl;

    return 0;
}
