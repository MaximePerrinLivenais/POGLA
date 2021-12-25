#pragma once

#include <memory>

#include "scene.hh"
#include "parser/option_parser.hh"
#include "utils/object_vbo.hh"

std::shared_ptr<Scene> build_scene(misc::Options& options);
