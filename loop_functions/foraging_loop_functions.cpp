#include "foraging_loop_functions.hpp"


namespace argos {

   void CForagingLoopFunctions::Init(TConfigurationNode& t_tree) {
      TConfigurationNode& paramsNode = GetNode(t_tree, "params");

      // initialize random number generator
      m_pcRNG = CRandom::CreateRNG("argos");

      // read arena size from configuration (for entity distribution)
      CVector3 arenaSize = GetSpace().GetArenaSize();
      Real halfX = arenaSize.GetX() / 2.0;
      Real halfY = arenaSize.GetY() / 2.0;

      // distribute food items in the environment
      GetNodeAttribute(paramsNode, "num_food_items", m_uNumFoodItems);
      for (uint32_t i = 0; i < m_uNumFoodItems; ++i) {
         // sample a random position within the arena bounds
         CVector3 position(
            m_pcRNG->Uniform(CRange<Real>(-halfX, halfX)),
            m_pcRNG->Uniform(CRange<Real>(-halfY, halfY)),
            0
         );
         // create a new LED entity to represent a food item
         CLEDEntity* ledEntity = new CLEDEntity(
            nullptr,
            "food_item_" + std::to_string(i),
            position,
            CColor::RED
         );
         AddEntity(*ledEntity);
         CLEDMedium& ledMedium = CSimulator::GetInstance().GetMedium<CLEDMedium>("leds");
         ledEntity->SetMedium(ledMedium);
         ledEntity->Enable();
         m_FoodItems[ledEntity->GetIndex()] = FoodItem(ledEntity->GetIndex(), std::nullopt, ledEntity);
      }
   }

   void CForagingLoopFunctions::PreStep() {
      
   }

   FoodItem& CForagingLoopFunctions::getFoodItem(uint32_t id) {
      return m_FoodItems[id];
   }

   REGISTER_LOOP_FUNCTIONS(CForagingLoopFunctions, "foraging_loop_functions");

}
