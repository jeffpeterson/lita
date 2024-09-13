#include <assert.h>

#include "ecs.h"

// Component names ('Position') use PascalCase
typedef struct Position {
  float x;
  float y; // Component members ('y') use snake_case
} Position;

typedef struct Velocity {
  float x;
  float y;
} Velocity;

// System names ('Move') use PascalCase. API types use snake_case_t
void Move(ecs_iter_t *it) {
  // Functions use snake_case
  Position *p = ecs_field(it, Position, 1);
  Velocity *v = ecs_field(it, Velocity, 2);

  for (int i = 0; i < it->count; i++) {
    p[i].x += v[i].x;
    p[i].y += v[i].y;
  }
}

void ecs_test() {
  ecs_world_t *world = ecs_init();

  // Declarative function-style macros use SCREAMING_SNAKE_CASE
  ECS_COMPONENT(world, Position);
  ECS_COMPONENT(world, Velocity);

  // Module names are PascalCase
  // ECS_IMPORT(world, MyModule);

  // Enumeration constants ('EcsOnUpdate') use PascalCase
  ECS_SYSTEM(world, Move, EcsOnUpdate, Position, Velocity);

  // Function wrapper macros use snake_case
  ecs_entity_t e = ecs_new(world);

  assert(e);

  // Builtin entities use PascalCase
  ecs_add(world, EcsWorld, Position);

  assert(ecs_fini(world) == 0);
}
