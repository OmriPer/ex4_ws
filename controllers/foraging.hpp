#include <argos3/core/control_interface/ci_controller.h>
#include <optional>

using namespace argos;

class ForagingController : public CCI_Controller {
public:

    ForagingController() {}
    virtual ~ForagingController() {}

    bool hasFood() { return m_carriedFoodId.has_value(); }
    uint32_t getCarriedFoodId() { return m_carriedFoodId.value(); }

protected:
    std::optional<uint32_t> m_carriedFoodId = std::nullopt;
};