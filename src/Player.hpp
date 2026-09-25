#pragma once

class Player
{
        private:
                int level = 0;

        public:
                
                void addLevel (int i)
                {
                        level += i;
                }

                void removeLevel (int i)
                {
                        level -= i;
                }

                void resetLevel ()
                {
                        level = 0;
                }

                int getLevel () const
                {
                        return level;
                }
};