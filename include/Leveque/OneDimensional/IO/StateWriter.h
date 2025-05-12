#pragma once

#include <filesystem>

#include <Leveque/OneDimensional/Grid/Grid.h>
#include <Leveque/OneDimensional/State/State.h>

namespace Jabre::Leveque::OneDimensional {
    void writeStateToCsvFile(const State& state, std::filesystem::path path);
}