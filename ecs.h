#pragma once

#include <cstdint>
#include <bitset>

namespace ecs{
// Entities have unique IDs
using entity_t = uint32_t;
const uint32_t MAX_ENTITIES = 5000;

// Component correspond to a bit in a bitfield
using component_t = uint8_t;
const uint8_t  MAX_COMPONENTS = 32;

// NOTE: May be able to optimize by not introducing this class
// Entities are given a bitfield signature contating all their component types
using signature_t = std::bitset<MAX_COMPONENTS>;

// Input
enum class InputButtons
{
	W,
	A,
	S,
	D,
	Q,
	E
};

// Events
using EventId = std::uint32_t;
using ParamId = std::uint32_t;
}
