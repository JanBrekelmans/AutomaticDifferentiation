#pragma once

#include <Leveque/OneDimensional/Grid/Grid.h>

#include <string>
#include <vector>

namespace Jabre::Leveque::OneDimensional {
    class Field {
       public:
        Field() = delete;
        Field(const Grid& grid, const std::string& name);

        const Grid& grid() const;
        const std::string& name() const;

        const std::vector<double>& values() const;
        std::vector<double>& values();

       private:
        const Grid& grid_;
        std::string name_;
        std::vector<double> values_;
        std::vector<double> auxilliaryValues_;
    };
}  // namespace Jabre::Leveque::OneDimensional