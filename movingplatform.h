
#include "StaticPlatform.h"

class MovingPlatform : public StaticPlatform {
public:
    MovingPlatform(float x, float y, float width, float height, int id);
    void update(float deltaTime) ;

private:
    float direction = 1.0f;
    float speed = 50.0f; // px/s
};
