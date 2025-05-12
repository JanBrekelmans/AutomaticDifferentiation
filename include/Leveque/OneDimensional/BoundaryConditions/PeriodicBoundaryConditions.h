#pragma once

#include "BoundaryConditions.h"

namespace Jabre::Leveque::OneDimensional {
    namespace internal {
        class LeftPeriodicBoundaryCondition : public LeftBoundaryCondition {
           public:
            using LeftBoundaryCondition::LeftBoundaryCondition;
            void applyOnLeft(Field& field) override;
        };

        class RightPeriodicBoundaryCondition : public RightBoundaryCondition {
           public:
            using RightBoundaryCondition::RightBoundaryCondition;
            void applyOnRight(Field& field) override;
        };
    }  // namespace internal

    class PeriodicBoundaryConditions : public BoundaryConditions {
       public:
        PeriodicBoundaryConditions(const std::string& fieldName);
    };
}  // namespace Jabre::Leveque::OneDimensional