using System.Collections.Generic;

namespace IvyyyAI
{
    public class IvyyyTowerBlock
    {
        int m_startX;
        int m_startY;

        //Amount of active towers in this block
        public int TowerCount { get; private set; }

        //Amount of soldiers in reach
        public int InReachCount { get; private set; }

        //Tower placement for this block
        private List<IvyyyPosition> m_towerSlots = new();
        public List<IvyyyPosition> TowerSlots => m_towerSlots;

        public IvyyyTowerBlock(int x, int y)
        {
            m_startX = x;
            m_startY = y;
        }

        public void Update(List<IvyyyPosition> enemyList, List<IvyyyPosition> towerList)
        {
            TowerCount = 0;
            InReachCount = 0;

            foreach (var towerPos in m_towerSlots)
            {
                foreach (var enemy in enemyList)
                {
                    if (IsPosInside(towerPos, enemy, 1, 8))
                        InReachCount++;
                }
            }

            foreach (var tower in towerList)
            {
                if (m_towerSlots.Contains (tower))
                    TowerCount++;
            }
        }

        private bool IsPosInside(IvyyyPosition rootPos, IvyyyPosition targetPos, int paddingX = 0, int paddingY = 0)
        {
            if (targetPos.x < rootPos.x - paddingX || targetPos.x > rootPos.x + paddingX
                || targetPos.y < (rootPos.y - paddingY) || targetPos.y > rootPos.y)
                return false;
            else
                return true;
        }

        public void SetTowerList (List<IvyyyPosition> towerList)
        {
            m_towerSlots.Clear();

            foreach (var tower in towerList)
            {
                IvyyyPosition pos = tower;
                pos.x += m_startX;
                pos.y += m_startY;
                m_towerSlots.Add(pos);
            }
        }
    }
}
