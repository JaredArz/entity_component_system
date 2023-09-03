#include <stdint.h>
#include <bitset>
#include <iostream>
#include <cassert>

namespace ecs{
// Entities have unique IDs
using entity_t = uint_fast32_t;
const uint_fast32_t MAX_ENTITIES = 5000;

// Component correspond to a bit in a bitfield
using component_type_t = uint8_t;
const uint8_t MAX_COMPONENTS = 32;

// NOTE: May be able to optimize by not introducing this class
// Entities are given a bitfield signature contating all their component types
using signature_t = std::bitset<MAX_COMPONENTS>;
}
