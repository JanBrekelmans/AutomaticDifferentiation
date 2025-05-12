#include "WaveStructure.h"

namespace Jabre::Leveque::OneDimensional {
    Wave::Wave(const State& state) {
        speed = std::vector<double>(state.grid().numTotalCells() - 1, 0.0);
        wave = std::vector<std::vector<double>>(
            state.fields().size(),
            std::vector<double>(state.grid().numTotalCells() - 1, 0.0));
    }

    WavesStructure::WavesStructure(const State& state, int numWaves) {
        amdq = std::vector<std::vector<double>>(
            state.fields().size(),
            std::vector<double>(state.grid().numTotalCells() - 1, 0.0));
        apdq = std::vector<std::vector<double>>(
            state.fields().size(),
            std::vector<double>(state.grid().numTotalCells() - 1, 0.0));
        waves = std::vector<Wave>(numWaves, Wave(state));
    }

    WavesStructureProvider::WavesStructureProvider(const State& state,
                                                   int numWaves)
        : wavesStructure_(state, numWaves) {}

    const WavesStructure& WavesStructureProvider::wavesStructure() const {
        return wavesStructure_;
    }
}  // namespace Jabre::Leveque::OneDimensional