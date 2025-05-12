#pragma once

#include <Leveque/OneDimensional/Grid/Grid.h>
#include <Leveque/OneDimensional/State/State.h>

#include <string>
#include <unordered_map>
#include <vector>

namespace Jabre::Leveque::OneDimensional {

    struct Wave {
        Wave() = delete;
        Wave(const State& state);

        std::vector<double> speed;
        std::vector<std::vector<double>> wave;
    };

    struct WavesStructure {
        WavesStructure() = delete;
        WavesStructure(const State& state, int numWaves);

        std::vector<std::vector<double>> amdq, apdq;
        std::vector<Wave> waves;
    };

    class WavesStructureProvider {
       public:
        WavesStructureProvider() = delete;
        WavesStructureProvider(const State& state, int numWaves);

        virtual void compute(const State& state) = 0;

        const WavesStructure& wavesStructure() const;

        virtual ~WavesStructureProvider() = default;

       protected:
        WavesStructure wavesStructure_;
    };
}  // namespace Jabre::Leveque::OneDimensional