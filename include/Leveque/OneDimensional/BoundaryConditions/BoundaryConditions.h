#pragma once

#include <Leveque/OneDimensional/Grid/Grid.h>
#include <Leveque/OneDimensional/State/Field.h>
#include <Leveque/OneDimensional/State/State.h>

#include <memory>
#include <string>

namespace Jabre::Leveque::OneDimensional {
    class DataManager;

    class LeftBoundaryCondition {
       public:
        LeftBoundaryCondition() = delete;
        LeftBoundaryCondition(const std::string& fieldName);

        virtual void applyOnLeft(Field& field) = 0;

        const std::string& fieldName() const;
        void setDataManager(const DataManager* const dataManagerPtr);

       protected:
        std::string fieldName_;
        const DataManager* dataManagerPtr_ = nullptr;
    };

    class RightBoundaryCondition {
       public:
        RightBoundaryCondition() = delete;
        RightBoundaryCondition(const std::string& fieldName);

        virtual void applyOnRight(Field& field) = 0;

        const std::string& fieldName() const;
        void setDataManager(const DataManager* const dataManagerPtr);

       protected:
        std::string fieldName_;
        const DataManager* dataManagerPtr_ = nullptr;
    };

    class BoundaryConditions {
       public:
        BoundaryConditions() = delete;
        BoundaryConditions(
            const std::string& fieldName,
            std::shared_ptr<LeftBoundaryCondition> leftBoundaryConditionPtr,
            std::shared_ptr<RightBoundaryCondition> rightBoundaryConditionPtr);

        void apply(Field& field);

        const std::string& fieldName() const;
        void setDataManager(const DataManager* const dataManagerPtr);

       private:
        std::string fieldName_;
        std::shared_ptr<LeftBoundaryCondition> leftBoundaryConditionPtr_;
        std::shared_ptr<RightBoundaryCondition> rightBoundaryConditionPtr_;
    };

}  // namespace Jabre::Leveque::OneDimensional