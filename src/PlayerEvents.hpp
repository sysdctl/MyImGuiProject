#pragma once

#include "Player.hpp"


namespace PlayerEvents {

        inline Player player;
        
        inline auto onLevelUp = [](){
                player.addLevel(1);
        };
        inline auto onLevelDown = [](){
                player.removeLevel(1);
        };
        inline auto onReset = [](){
                player.resetLevel();
        };
        inline auto onAdd5Level = [](){
                player.addLevel(5);
        };
        inline auto onAddLevel = [](int i){
                player.addLevel(i);
        };

        inline auto changeStatus = [](std::string** status){
                **status = "Player Leveled Up!";
        };
        inline void onLevelUpChangeStatus(std::string* status)
        {
                onLevelUp();
                changeStatus(&status);
        }
}
