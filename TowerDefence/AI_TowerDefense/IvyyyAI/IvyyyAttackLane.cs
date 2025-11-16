using AI_Strategy;
using GameFramework;
using System.Collections.Generic;

namespace IvyyyAI
{
    public class IvyyyAttackLane
    {
        private int m_startX;
        private int m_width;

        //public int EnemyTowerCount {get;private set;}
        public int EnemyTowerHp { get; private set; }

        public int FriendlySoldierStandByCount { get; private set; }
        public int Width => m_width;
        public int StartIndex => m_startX;

        public IvyyyAttackLane (int x, int w)
        {
            m_startX = x;
            m_width = w;
        }

        public void Update(List<IvyyySoldier> friendlySoldierList, List<Tower> enemyTowerList)
        {
            FriendlySoldierStandByCount = 0;

            foreach (var item in friendlySoldierList)
            {
                bool onLaneZero = item.PosY == 0;
                bool onStandy = item.PosY >= 0 && item.PosY < 3;
                bool onLane = item.PosX >= m_startX && item.PosX < m_startX + m_width;

                if (!onLane)
                    continue;

                if (onStandy)
                    FriendlySoldierStandByCount++;
            }

            //EnemyTowerCount = 0;
            EnemyTowerHp = 0;

            foreach (var item in enemyTowerList)
            {
                bool inRange = item.PosX >= m_startX - 2 && item.PosX < m_startX + m_width + 2;

                if (!inRange)
                    continue;

                //EnemyTowerCount++;
                EnemyTowerHp += item.Health;
            }
        }
    }
}
