using System.Collections.Generic;

namespace IvyyyAI
{
    public class IvyyyTowerBlock
    {
        int m_startX;
        int m_startY;


        public int SoldierCount { get; private set; }
        public int TowerCount { get; private set; }
        public int ThreatenedCount { get; private set; }
        public int InReachCount { get; private set; }
        public float RatingLevel { get; private set; }

        private List<IvyyyPosition> m_towerSlots = new();
        public List<IvyyyPosition> TowerSlots => m_towerSlots;

        public IvyyyTowerBlock(int x, int y)
        {
            m_startX = x;
            m_startY = y;
        }

        public void Update(List<IvyyyPosition> enemyList, List<IvyyyPosition> towerList)
        {
            SoldierCount = 0;
            TowerCount = 0;
            ThreatenedCount = 0;
            InReachCount = 0;
            RatingLevel = 0;

            foreach (var towerPos in m_towerSlots)
            {
                foreach (var enemy in enemyList)
                {
                    if (IsPosInside(towerPos, enemy, 1))
                    {
                        InReachCount++;
                        ThreatenedCount++;
                    }
                    else if (IsPosInside(towerPos, enemy, 2))
                        InReachCount++;
                }
            }

            foreach (var tower in towerList)
            {
                if (m_towerSlots.Contains (tower))
                    TowerCount++;
            }
        }

        private bool IsPosInside(IvyyyPosition rootPos, IvyyyPosition targetPos, int padding = 0)
        {
            if (targetPos.x < rootPos.x - padding || targetPos.x > rootPos.x + padding
                || targetPos.y < (rootPos.y - padding - 1) || targetPos.y > rootPos.y + padding)
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
