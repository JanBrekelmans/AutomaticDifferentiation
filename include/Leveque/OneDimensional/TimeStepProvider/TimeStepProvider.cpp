#include "TimeStepProvider.h"

namespace Jabre::Leveque::OneDimensional {
    double TimeStepProvider::get() const {
        return dt_;
    }

    void TimeStepProvider::compute(
        const State& state,
        const WavesStructureProvider& waveStructureProvider) {
        dt_ = computeInternal(state, waveStructureProvider);
    }
}  // namespace Jabre::Leveque::OneDimensional