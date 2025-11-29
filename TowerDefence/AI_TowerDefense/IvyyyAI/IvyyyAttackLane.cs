using GameFramework;
using System.Collections.Generic;

namespace IvyyyAI
{
    public class IvyyyAttackLane
    {
        //row start index
        private int m_startX;

        //soldiers per row
        private int m_width;

        //target amount for soldier rows
        private int m_depth;

        //Combined hp of all encountered towers on this lane
        public int EnemyTowerCount { get; private set; }

        public int Width => m_width;
        public int Depth => m_depth;
        public int StartIndex => m_startX;

        //required goold to build the complete regiment
        public int RequierdGold => m_width * m_depth * 2;

        public IvyyyAttackLane (int x, int w, int d)
        {
            m_startX = x;
            m_width = w;
            m_depth = d;
        }

        public void Update(List<IvyyySoldier> friendlySoldierList, List<Tower> enemyTowerList)
        {
            EnemyTowerCount = 0;

            foreach (var item in enemyTowerList)
            {
                bool isDangerous = item.PosX >= m_startX - 2 && item.PosX < m_startX + m_width + 3;

                if (!isDangerous)
                    continue;

                EnemyTowerCount++;
            }
        }
    }
}
