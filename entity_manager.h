#include "ecs.h"
#include <queue>
#include <cassert>
#include <array>

namespace e_mgr{

class entity_manager{
    public:
        entity_manager(){
            // NOTE CHECK NAME SPACE ENTITY
            // Initialize the available entities queue with all possible entity IDs
            for ( ecs::entity_t new_entity = 0; new_entity < ecs::MAX_ENTITIES; ++new_entity ){
                available_entities.push(new_entity);
           }
        }

        ecs::entity_t create_entity(){
            assert( living_entity_count < ecs::MAX_ENTITIES && "Too many entities in existence.");

            // Take an ID from the front of queue
            ecs::entity_t id = available_entities.front();
            available_entities.pop();
            ++living_entity_count;

            return id;
        }

        void destroy_entity(ecs::entity_t entity){
            assert( entity < ecs::MAX_ENTITIES && "Invalid entity, out of range.");

            // Invalidate the destroyed entity's signature
            e_signatures[entity].reset();

            // Put the destroyed ID at the back of the queue
            available_entities.push(entity);
            --living_entity_count;
        }

        void set_signature(ecs::entity_t entity, ecs::signature_t signature){
            assert( entity < ecs::MAX_ENTITIES && "Invalid entity, out of range.");

            e_signatures[entity] = signature;
        }

        ecs::signature_t get_signature(ecs::entity_t entity){
            assert( entity < ecs::MAX_ENTITIES && "Invalid entity, out of range.");

            return e_signatures[entity];
        }

    private:

        // Queue of unused entity IDs
        std::queue<ecs::entity_t> available_entities{};
        
        // Array of signatures where the index corresponds to the entity ID
        std::array<ecs::signature_t, ecs::MAX_ENTITIES> e_signatures{};

        // total living entities - used to keep limits on how many exist
        uint32_t living_entity_count{};
    };
}
