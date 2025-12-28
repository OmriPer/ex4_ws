#pragma once

#include <argos3/core/simulator/loop_functions.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/simulator/media/led_medium.h>
#include <argos3/plugins/simulator/entities/led_entity.h>
#include <argos3/core/utility/math/rng.h>

#include <optional>

namespace argos {

   struct FoodItem {
         uint32_t food_id;
         std::optional<uint32_t> carrier_id; // empty if not carried
         bool processed = false;
         CLEDEntity* ledEntity;

      FoodItem() : food_id(0), carrier_id(std::nullopt), ledEntity(nullptr) {};

      FoodItem(uint32_t food_id_, std::optional<uint32_t> carrier_id_, CLEDEntity* ledEntity_)
         : food_id(food_id_), carrier_id(carrier_id_), ledEntity(ledEntity_) {};
   };

   class CForagingLoopFunctions : public CLoopFunctions {

   public:

      CForagingLoopFunctions() {}
      virtual ~CForagingLoopFunctions() {}

      FoodItem& getFoodItem(uint32_t id);

      void Init(TConfigurationNode& t_tree) override;
      void PreStep() override;

   private:

      CRandom::CRNG* m_pcRNG = nullptr;
      uint32_t m_uNumFoodItems;

      std::map<int, FoodItem> m_FoodItems; // map: CLEDEntity ID -> FoodItem

   };
}
