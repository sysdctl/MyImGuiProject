#pragma once

#include "Player.hpp"
inline Player player;

namespace PlayerEvents {

    inline auto onLevelUp = [](){
            player.addLevel(1);
    };
    inline auto onLevelDown = [](){
            player.removeLevel(1);
    };
    inline auto onReset = [](){
            player.resetLevel();
    };
    
}
