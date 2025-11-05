using System.Collections.Generic;

namespace IvyyyAI
{
    public class IvyyyTowerBlock
    {
        int m_startX;
        int m_startY;
        int m_colums;
        int m_rows;

        public int SoldierCount { get; private set; }
        public int TowerCount { get; private set; }
        public int ThreatenedCount { get; private set; }
        public int InReachCount { get; private set; }
        public float RatingLevel { get; private set; }

        public int X => m_startX;
        public int Y => m_startY;

        private List<IvyyyPosition> m_towerSlots = new();
        public List<IvyyyPosition> TowerSlots => m_towerSlots;

        public IvyyyTowerBlock(int x, int y, int c, int r)
        {
            m_startX = x;
            m_startY = y;
            m_colums = c;
            m_rows = r;
        }

        public void Update(List<IvyyyPosition> enemyList, List<IvyyyPosition> towerList)
        {
            SoldierCount = 0;
            TowerCount = 0;
            ThreatenedCount = 0;
            InReachCount = 0;
            RatingLevel = 0;

            foreach (var enemy in enemyList)
            {
                if (IsPosInside(enemy))
                    SoldierCount++;
                else if (IsPosInside(enemy, 1))
                {
                    InReachCount++;
                    ThreatenedCount++;
                }
                else if (IsPosInside(enemy, 2))
                    InReachCount++;
            }

            foreach (var tower in towerList)
            {
                if (IsPosInside(tower))
                    TowerCount++;
            }
        }

        private bool IsPosInside(IvyyyPosition pos, int padding = 0)
        {
            if (pos.x < m_startX - padding || pos.x > m_startX + m_colums + padding
                || pos.y < m_startY - padding || pos.y > m_startY + m_rows + padding)
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
