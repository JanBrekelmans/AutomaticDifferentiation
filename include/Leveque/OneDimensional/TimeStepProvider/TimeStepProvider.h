#pragma once

#include <Leveque/OneDimensional/State/State.h>
#include <Leveque/OneDimensional/WaveStructure/WaveStructure.h>

namespace Jabre::Leveque::OneDimensional {
    class TimeStepProvider {
       public:
        double get() const;
        void compute(const State& state,
                     const WavesStructureProvider& waveStructureProvider);

       protected:
        virtual double computeInternal(
            const State& state,
            const WavesStructureProvider& waveStructureProvider) = 0;

       private:
        double dt_;
    };
}  // namespace Jabre::Leveque::OneDimensional