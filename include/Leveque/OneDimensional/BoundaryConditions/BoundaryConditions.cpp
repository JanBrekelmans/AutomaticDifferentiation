#include "BoundaryConditions.h"

namespace Jabre::Leveque::OneDimensional {
    LeftBoundaryCondition::LeftBoundaryCondition(const std::string& fieldName)
        : fieldName_(fieldName) {}

    const std::string& LeftBoundaryCondition::fieldName() const {
        return fieldName_;
    }

    void LeftBoundaryCondition::setDataManager(
        const DataManager* const dataManagerPtr) {
        dataManagerPtr_ = dataManagerPtr;
    }

    RightBoundaryCondition::RightBoundaryCondition(const std::string& fieldName)
        : fieldName_(fieldName) {}

    const std::string& RightBoundaryCondition::fieldName() const {
        return fieldName_;
    }

    void RightBoundaryCondition::setDataManager(
        const DataManager* const dataManagerPtr) {
        dataManagerPtr_ = dataManagerPtr;
    }

    BoundaryConditions::BoundaryConditions(
        const std::string& fieldName,
        std::shared_ptr<LeftBoundaryCondition> leftBoundaryConditionPtr,
        std::shared_ptr<RightBoundaryCondition> rightBoundaryConditionPtr)
        : fieldName_(fieldName),
          leftBoundaryConditionPtr_(leftBoundaryConditionPtr),
          rightBoundaryConditionPtr_(rightBoundaryConditionPtr) {}

    void BoundaryConditions::apply(Field& field) {
        leftBoundaryConditionPtr_->applyOnLeft(field);
        rightBoundaryConditionPtr_->applyOnRight(field);
    }

    const std::string& BoundaryConditions::fieldName() const {
        return fieldName_;
    }

    void BoundaryConditions::setDataManager(
        const DataManager* const dataManagerPtr_) {
        leftBoundaryConditionPtr_->setDataManager(dataManagerPtr_);
        rightBoundaryConditionPtr_->setDataManager(dataManagerPtr_);
    }

}  // namespace Jabre::Leveque::OneDimensiona