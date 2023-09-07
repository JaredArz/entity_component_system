#include "ecs.h"
#include "component_array.h"
#include <cassert>
#include <typeinfo>
#include <memory>

namespace c_mgr{

class component_manager{

public:
    template<typename T>
    void register_component(){
        const char* type_name = typeid(T).name();
        assert(comp_types.find(type_name) == comp_types.end() && "Registering component more than once.");

        // Add this component type to the component type map
        comp_types.insert({type_name, next_comp_type});

        // Create a component array pointer and add it to the component arrays map
        comp_arrs.insert({type_name, std::make_shared<c_arr::component_array<T>>()});

        ++next_comp_type;
    }

    template<typename T>
    ecs::component_t get_component_type(){
        const char* type_name = typeid(T).name();
        assert(comp_types.find(type_name) != comp_types.end() && "Component not registered before use.");

        // Return this components type - used for creating signatures
        return comp_types[type_name];
    }

    template<typename T>
    void add_component(ecs::entity_t entity, T component){
        // Add a componenet to the array for an entity
        get_component_array<T>()->insert_data(entity,component);
    }

    template<typename T>
    void remove_component(ecs::entity_t entity){
        // Remove a componenet from the array for an entity
        get_component_array<T>()->remove_data(entity);
    }

    template<typename T>
    ecs::component_t get_component(ecs::entity_t entity){
        // Get a reference to a component from the array for an entity
        return get_component_array<T>()->get_data(entity);
    }

    void entity_destroyed(ecs::entity_t entity){
        // Notify each component array that an entity has been destroyed
        // If it has a component for that entity, it will remove it
        for (auto const& pair : comp_arrs){
            auto const& component = pair.second;
            component->entity_destroyed(entity);
        }
    }

private:
    // Map from type string pointer to a component type
    std::unordered_map<const char*, ecs::component_t> comp_types{};

    // Map from type string pointer to a component array
    std::unordered_map<const char*, std::shared_ptr<c_arr::iface_component_array>> comp_arrs{};

    // The component type to be assigned to the next registered component - starting at 0
    ecs::component_t next_comp_type{};

    // Convience function to get the statically casted pointer to the componenet array of type T
    template<typename T>
    std::shared_ptr<c_arr::component_array<T>> get_component_array(){
        const char* type_name = typeid(T).name();
        assert(comp_types.find(type_name) != comp_types.end() && "Component not registered before use.");
        
        return std::static_pointer_cast<c_arr::component_array<T>>(comp_arrs[type_name]);
    }
};
}
