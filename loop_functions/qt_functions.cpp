#include "qt_functions.hpp"

using namespace argos;

/****************************************/
/****************************************/

CQTFunctions::CQTFunctions() :
    m_cForagingLF(dynamic_cast<CForagingLoopFunctions&>(CSimulator::GetInstance().GetLoopFunctions())) {
        // RegisterUserFunction<CQTFunctions,CPiPuckEntity>(&CQTFunctions::Draw);
        RegisterUserFunction<CQTFunctions,CLEDEntity>(&CQTFunctions::Draw);
}

/****************************************/
/****************************************/

// void CQTFunctions::Draw(CPiPuckEntity& c_entity) {
//     ForagingController& controller = dynamic_cast<ForagingController&>(c_entity.GetControllableEntity().GetController());
    
//     // Draw() is invoked in world coordinates for composable entities; use the embodied origin.
//     const CVector3& cRobotPos = c_entity.GetEmbodiedEntity().GetOriginAnchor().Position;

//    if(controller.hasFood()) {
//       FoodItem& pcFood = m_cForagingLF.GetFoodItem(controller.getCarriedFoodId());
//       if(&pcFood) {
//           // Render the carried food as a cylinder above the robot.
//           // Processed/dropped food is yellow; otherwise black.
//           DrawCylinder(
//               cRobotPos + CVector3(0.0f, 0.0f, 0.1f), // position slightly above robot
//               CQuaternion(),
//               m_cForagingLF.GetFoodRadius(),
//               FOOD_HEIGHT,
//               pcFood.ledEntity->GetColor()
//           );
//       } else {
//           THROW_ARGOSEXCEPTION("Robot " << fController.GetId() << " says it has food, but no food entity is mapped to it in loop functions.");
//       }
//    }

//    // draw robot state text
//    Task* currentTaskPtr = fController.getCurrentTask();
//    if(currentTaskPtr == nullptr) {
//        return;
//    }
//    std::string currentTaskName = fController.GetId() + "-" + currentTaskPtr->getName();
//    DrawText(cRobotPos + CVector3(0.0f, 0.0f, 0.2f), currentTaskName);
// }

void CQTFunctions::Draw(CLEDEntity& c_entity) {
    FoodItem& cFoodItem = m_cForagingLF.getFoodItem(c_entity.GetIndex());
    // only draw uncarried food items (on the ground), as carried food items are drawn by the pipuck Draw()
    if (cFoodItem.carrier_id.has_value()) {
        return;
    }

    // Draw food items as cylinders on the ground
    CVector3 cFoodPos = c_entity.GetPosition();
    DrawCylinder(
        CVector3(cFoodPos.GetX(), cFoodPos.GetY(), FOOD_HEIGHT / 2), // position on ground
        CQuaternion(),
        FOOD_RADIUS,
        FOOD_HEIGHT,
        cFoodItem.processed ? CColor::YELLOW : CColor::GRAY80
    );
}

// void CQTFunctions::DrawInWorld() {
//     DrawText(
//         CVector3(m_cForagingLF.getBase1().GetX(), m_cForagingLF.getBase1().GetY(), 0.3), // position
//         "base1" //text
//     );
//     DrawText(
//         CVector3(m_cForagingLF.getBase2().GetX(), m_cForagingLF.getBase2().GetY(), 0.3), // position
//         "base2" // text
//     );
// }

/****************************************/
/****************************************/

REGISTER_QTOPENGL_USER_FUNCTIONS(CQTFunctions, "qt_functions")
