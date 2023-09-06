#include "ecs.h"
#include <queue>
#include <cassert>
#include <array>
#define assert_in_range(object, max) assert( object < max && "Invalid entity, out of range.")
#define assert_is_space(count, max)  assert( count  < max && "Too many entities in existence.")

//extern const uint32_t ecs::MAX_ENTITIES;
//extern const uint8_t  ecs::MAX_COMPONENTS;

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
            assert_is_space(living_entity_count, ecs::MAX_ENTITIES);

            // Take an ID from the front of queue
            ecs::entity_t id = available_entities.front();
            available_entities.pop();
            ++living_entity_count;

            return id;
        }

        void destroy_entity(ecs::entity_t entity){
            assert_in_range(entity, ecs::MAX_ENTITIES);

            // Invalidate the destroyed entity's signature
            e_signatures[entity].reset();

            // Put the destroyed ID at the back of the queue
            available_entities.push(entity);
            --living_entity_count;
        }

        void set_signature(ecs::entity_t entity, ecs::signature_t signature){
            assert_in_range(entity, ecs::MAX_ENTITIES);

            e_signatures[entity] = signature;
        }

        ecs::signature_t get_signature(ecs::entity_t entity){
            assert_in_range(entity, ecs::MAX_ENTITIES);

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
