#pragma once

#include <argos3/core/simulator/loop_functions.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/simulator/media/led_medium.h>
#include <argos3/plugins/simulator/entities/led_entity.h>
#include <argos3/plugins/robots/pi-puck/simulator/pipuck_entity.h>
#include <argos3/core/utility/math/rng.h>
#include <foraging.hpp>

#include <optional>

namespace argos {

   struct FoodItem {
         uint32_t food_id;
         std::optional<uint32_t> carrier_id; // empty if not carried
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
      const std::vector<CVector3>& getBases1() const { return m_Bases1; }
      const std::vector<CVector3>& getBases2() const { return m_Bases2; }
      const CColor& GetTeamColor(uint8_t team) const { return (team == 1) ? m_Team1Color : m_Team2Color; }

      void Init(TConfigurationNode& t_tree) override;
      void PreStep() override;
      void PostExperiment() override;

      static constexpr Real PICKUP_RADIUS_SQRD = 0.05 * 0.05; // radius within which a pipuck can pick up food
      static constexpr Real BASE_RADIUS = 0.1; // radius of base area

   private:

      CRandom::CRNG* m_pcRNG = nullptr;
      uint32_t m_uNumFoodItems;

      std::map<int, FoodItem> m_FoodItems; // map: CLEDEntity ID -> FoodItem
      // Base positions
      std::vector<CVector3> m_Bases1; // team1 base positions
      std::vector<CVector3> m_Bases2; // team2 base positions
      // Team colors
      CColor m_Team1Color; // team1 color
      CColor m_Team2Color; // team2 color
      // Team Scores
      uint32_t m_Team1Score = 0;
      uint32_t m_Team2Score = 0;

      bool m_bLazyInitialized = false;
   };
}
