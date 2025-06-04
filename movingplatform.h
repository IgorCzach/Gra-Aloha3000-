
#include "StaticPlatform.h"

class MovingPlatform : public StaticPlatform {
public:
    MovingPlatform(float x, float y, float width, float height, int id);
    void update(float deltaTime) override;

private:
    float direction;
    float speed = 150.0f;
};
