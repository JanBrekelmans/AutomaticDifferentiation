#include "DataManager.h"

namespace Jabre::Leveque::OneDimensional {
    DataManager::Builder& DataManager::Builder::withGrid(Grid grid) {
        gridPtr_ = std::make_unique<Grid>(std::move(grid));
        return *this;
    }

    DataManager::Builder& DataManager::Builder::withFieldNames(
        std::vector<std::string> fieldNames) {
        fieldNames_ = std::move(fieldNames);
        return *this;
    }

    DataManager::Builder& DataManager::Builder::withBoundaryConditions(
        std::unordered_map<std::string, BoundaryConditions>
            boundaryConditionsMap) {
        boundaryConditionsMap_ = std::move(boundaryConditionsMap);
        return *this;
    }

    DataManager::Builder& DataManager::Builder::withWaveStructureProvider(
        std::unique_ptr<WavesStructureProvider> waveStructureProviderPtr) {
        wavesStructureProviderPtr_ = std::move(waveStructureProviderPtr);
        return *this;
    }

    DataManager::Builder& DataManager::Builder::withTimeStepProvider(
        std::unique_ptr<TimeStepProvider> timeStepProviderPtr) {
        timeStepProviderPtr_ = std::move(timeStepProviderPtr);
        return *this;
    }

    DataManager DataManager::Builder::build() {
        return DataManager(*this);
    }

    const Grid& DataManager::grid() const {
        return grid_;
    }

    const State& DataManager::currentState() const {
        return *currentStatePtr_;
    }

    State& DataManager::currentState() {
        return *currentStatePtr_;
    }

    const State& DataManager::oldState() const {
        return *oldStatePtr_;
    }

    State& DataManager::oldState() {
        return *oldStatePtr_;
    }

    void DataManager::swapStates() {
        std::swap(currentStatePtr_, oldStatePtr_);
    }

    DataManager::DataManager(Builder& builder)
        : grid_(std::move(*builder.gridPtr_)) {
        currentStatePtr_ = std::make_unique<State>(grid_, builder.fieldNames_);
        oldStatePtr_ = std::make_unique<State>(grid_, builder.fieldNames_);
        boundaryConditionsMap_ = std::move(builder.boundaryConditionsMap_);
        wavesStructureProviderPtr_ =
            std::move(builder.wavesStructureProviderPtr_);
        timeStepProviderPtr_ = std::move(builder.timeStepProviderPtr_);
    }
}  // namespace Jabre::Leveque::OneDimensional