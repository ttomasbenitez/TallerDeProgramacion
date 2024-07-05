#ifndef AGENT_H
#define AGENT_H
class Agent
{
protected:
    int posX;
    int posY;
    float currentLife;

public:
    float getCurrentLife();
    int getPosX();
    int getPosY();
};

#endif
