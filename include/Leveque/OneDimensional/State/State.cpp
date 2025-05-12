#include "State.h"

#include <stdexcept>

namespace Jabre::Leveque::OneDimensional {
    State::State(const Grid& grid, const std::vector<std::string>& fieldNames,
                 const std::vector<std::string>& auxilliaryFieldNames)
        : grid_(grid) {
        for (int i = 0; i < fieldNames.size(); i++) {
            const auto& fieldName = fieldNames[i];
            nameToIndexMap_.emplace(fieldName, i);
            fields_.push_back(Field(grid, fieldName));
        }

        for (int i = 0; i < auxilliaryFieldNames.size(); i++) {
            const auto& auxilliaryFieldName = auxilliaryFieldNames[i];
            auxilliaryNameToIndexMap_.emplace(auxilliaryFieldName, i);
            auxilliaryFields_.push_back(Field(grid, auxilliaryFieldName));
        }
    }

    State::State(const Grid& grid, const std::vector<std::string>& fieldNames)
        : State(grid, fieldNames, {}) {}

    const std::vector<Field>& State::fields() const {
        return fields_;
    }

    std::vector<Field>& State::fields() {
        return fields_;
    }

    const Field& State::field(const std::string& fieldName) const {
        auto it = nameToIndexMap_.find(fieldName);
        if (it != nameToIndexMap_.end()) {
            return fields_[it->second];
        }
        throw std::runtime_error("Could not find field: " + fieldName);
    }

    Field& State::field(const std::string& fieldName) {
        auto it = nameToIndexMap_.find(fieldName);
        if (it != nameToIndexMap_.end()) {
            return fields_[it->second];
        }
        throw std::runtime_error("Could not find field: " + fieldName);
    }

    const std::vector<Field>& State::auxilliaryFields() const {
        return auxilliaryFields_;
    }

    std::vector<Field>& State::auxilliaryFields() {
        return auxilliaryFields_;
    }

    const Field& State::auxilliaryField(
        const std::string& auxilliaryFieldName) const {
        auto it = auxilliaryNameToIndexMap_.find(auxilliaryFieldName);
        if (it != auxilliaryNameToIndexMap_.end()) {
            return auxilliaryFields_[it->second];
        }
        throw std::runtime_error("Could not find auxilliary field: " +
                                 auxilliaryFieldName);
    }

    Field& State::auxilliaryField(const std::string& auxilliaryFieldName) {
        auto it = auxilliaryNameToIndexMap_.find(auxilliaryFieldName);
        if (it != auxilliaryNameToIndexMap_.end()) {
            return auxilliaryFields_[it->second];
        }
        throw std::runtime_error("Could not find auxilliary field: " +
                                 auxilliaryFieldName);
    }

    double State::time() const {
        return time_;
    }

    double& State::time() {
        return time_;
    }
}  // namespace Jabre::Leveque::OneDimensional
