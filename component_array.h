#include "ecs.h"
#include <unordered_map>

// NOTE: fix? only checks if the last added componenet matches, not sure how .end works
#define assert_ent_has_comp(e_to_i_map, e) assert( e_to_i_map(e) == e_to_i_map.end() && "Component added to same entity more than once.")
#define assert_ent_not_have_comp(e_to_i_map, e) assert( e_to_i_map(e) != e_to_i_map.end() && "Non-existent component access in entity.")


// interface is needed so that the component manager can tell a generic componenet array that an entity
// has been destroyed and that it needs to update its array mappings
class iface_component_array
    public:
        // virtual destructor to prevent undefined behavior/memory leaks in inheritance
        virtual ~iface_component_array() = default;
        virtual void entity_destroyed(ecs::entity_t entity) = 0;
};


// virtual functions (the above interface) can be redefined in derived classes
// class <derived> : public <base>
template<typename T> // allow for arbitrary component ( some struct )
class component_array : public iface_component_array{
public:
    void insert_data(ecs:entity_t entity, T component){
        assert_ent_has_comp(entity_to_index_map, entity);

        // Put new entry at end and update the maps
        size_t new_index = map_size;
        entity_to_index_map[entity] = new_index;
        index_to_entity_map[new_index] entity;
        component_array[new_index] = component;
        ++map_size;
    }

    void remove_data(ecs:entity_t entity){
        assert_ent_not_have_comp(entity_to_index_map, entity);

        // Copy element at end into deleted element's place to maintain density
        size_t index_of_removed = entity_to_index_map[entity];
        size_t index_of_last    = map_size - 1;
        component_array[index_of_removed] = component_array[index_of_last];

        // Update map to point to moved spot
        ecs:entity_t entity_at_last = index_to_entity_map[index_of_last];
        entity_to_index_map[entity_of_last]   = index_of_removed;
        index_to_entity_map[index_of_removed] = component_array[index_of_last];

        // perform removal
        entity_to_index_map.erase(entity);
        index_to_entity_map.erase(index_of_last);

        --map_size;
    }


    // NOTE wtf is this reference
    T& GetData(ecs::entity_t entity){
        assert_ent_not_have_comp(entity_to_index_map, entity);

        //return reference to entitiy's component
        return component_array[ entity_to_index_map[entity] ];
    }

    void entity_destroyed(ecs:entity_t entity) override
    {
        // NOTE invokes redundant assert
        if (entity_to_index_map.find(entity) != entity_to_index_map.end())
            remove_data(entity);
    }

private:
    ;//FIXME


