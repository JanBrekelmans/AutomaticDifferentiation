#pragma once

#include <Leveque/OneDimensional/Grid/Grid.h>
#include <Leveque/OneDimensional/State/Field.h>

#include <string>
#include <unordered_map>
#include <vector>

namespace Jabre::Leveque::OneDimensional {
    class State {
       public:
        State() = delete;
        State(const Grid& grid, const std::vector<std::string>& fieldNames,
              const std::vector<std::string>& auxilliaryFieldNames);
        State(const Grid& grid, const std::vector<std::string>& fieldNames);

        const Grid& grid() const;

        const std::vector<Field>& fields() const;
        std::vector<Field>& fields();

        const Field& field(const std::string& fieldName) const;
        Field& field(const std::string& fieldName);

        const std::vector<Field>& auxilliaryFields() const;
        std::vector<Field>& auxilliaryFields();

        const Field& auxilliaryField(
            const std::string& auxilliaryFieldName) const;
        Field& auxilliaryField(const std::string& auxilliaryFieldName);

        double time() const;
        double& time();

       private:
        const Grid& grid_;
        std::vector<Field> fields_;
        std::vector<Field> auxilliaryFields_;
        std::unordered_map<std::string, int> nameToIndexMap_,
            auxilliaryNameToIndexMap_;
        double time_ = 0.0;
    };
}  // namespace Jabre::Leveque::OneDimensional