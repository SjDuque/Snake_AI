#ifndef GAME_I_HPP
#define GAME_I_HPP

#include "interfaces/controller_i.hpp"

class GameI {
    private:
    /**
     * @brief Input controller
     * 
     */
    ControllerI* input;
    
    public:
    /**
     * @brief Return if game is alive
     * 
     * @return true alive
     * @return false dead
     */
    virtual const bool alive() = 0;
    
    /**
     * @brief Start new game
     * 
     */
    virtual void reset() = 0;
    
    /**
     * @brief Update function
     * 
     */
    virtual void update() = 0;
    
    /**
     * @brief Draw function using RayLib
     * 
     */
    virtual void draw() = 0;
};

#endif