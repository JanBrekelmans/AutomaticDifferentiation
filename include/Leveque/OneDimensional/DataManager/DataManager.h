#pragma once

#include <Leveque/OneDimensional/BoundaryConditions/BoundaryConditions.h>
#include <Leveque/OneDimensional/Grid/Grid.h>
#include <Leveque/OneDimensional/State/Field.h>
#include <Leveque/OneDimensional/State/State.h>
#include <Leveque/OneDimensional/WaveStructure/WaveStructure.h>
#include <Leveque/OneDimensional/TimeStepProvider/TimeStepProvider.h>

#include <memory>

namespace Jabre::Leveque::OneDimensional {

    class DataManager {
       public:
        class Builder {
           public:
            Builder() = default;
            Builder& withGrid(Grid grid);
            Builder& withFieldNames(std::vector<std::string> fieldNames);
            Builder& withBoundaryConditions(
                std::unordered_map<std::string, BoundaryConditions>
                    boundaryConditionsMap);
            Builder& withWaveStructureProvider(
                std::unique_ptr<WavesStructureProvider>
                    waveStructureProviderPtr);
            Builder& withTimeStepProvider(
                std::unique_ptr<TimeStepProvider> timeStepProviderPtr);

            DataManager build();

           private:
            std::unique_ptr<Grid> gridPtr_;
            std::vector<std::string> fieldNames_;
            std::unordered_map<std::string, BoundaryConditions>
                boundaryConditionsMap_;
            std::unique_ptr<WavesStructureProvider> wavesStructureProviderPtr_;
            std::unique_ptr<TimeStepProvider> timeStepProviderPtr_;

            friend DataManager;
        };

        const Grid& grid() const;

        const State& currentState() const;
        State& currentState();
        const State& oldState() const;
        State& oldState();

        void swapStates();

       private:
        DataManager(Builder& builder);

        Grid grid_;
        std::unique_ptr<State> currentStatePtr_, oldStatePtr_;
        std::unordered_map<std::string, BoundaryConditions>
            boundaryConditionsMap_;
        std::unique_ptr<WavesStructureProvider> wavesStructureProviderPtr_;
        std::unique_ptr<TimeStepProvider> timeStepProviderPtr_;

        friend DataManager::Builder;
    };
}  // namespace Jabre::Leveque::OneDimensional