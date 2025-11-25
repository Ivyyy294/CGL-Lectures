using AI_Strategy;
using GameFramework;
using System.Collections.Generic;

namespace IvyyyAI
{
    public class IvyyyAttackLane
    {
        private int m_startX;
        private int m_width;
        private int m_depth;

        //public int EnemyTowerCount {get;private set;}
        public int EnemyTowerHp { get; private set; }
        public int EnemyTowerInReach { get; private set; }

        public int FriendlySoldierStandByCount { get; private set; }
        public int Width => m_width;
        public int Depth => m_depth;
        public int StartIndex => m_startX;
        public int RequierdGold => m_width * m_depth * 2;

        public IvyyyAttackLane (int x, int w)
        {
            m_startX = x;
            m_width = w;
            m_depth = 9;
        }

        public void Update(List<IvyyySoldier> friendlySoldierList, List<Tower> enemyTowerList)
        {
            FriendlySoldierStandByCount = 0;

            foreach (var item in friendlySoldierList)
            {
                bool onLaneZero = item.PosY == 0;
                bool onStandy = item.PosY >= 0 && item.PosY < Depth;
                bool onLane = item.PosX >= m_startX && item.PosX < m_startX + m_width;

                if (!onLane)
                    continue;

                if (onStandy)
                    FriendlySoldierStandByCount++;
            }

            //EnemyTowerCount = 0;
            EnemyTowerHp = 0;
            EnemyTowerInReach = 0;

            foreach (var item in enemyTowerList)
            {
                bool isDangerous = item.PosX >= m_startX - 2 && item.PosX < m_startX + m_width + 3;
                bool inRange = item.PosX >= m_startX - 1 && item.PosX < m_startX + m_width + 1;

                if (!isDangerous)
                    continue;

                //EnemyTowerCount++;
                EnemyTowerHp += item.Health;
                
                if (inRange)
                    EnemyTowerInReach++;
            }
        }
    }
}
