using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AI_Strategy
{
    public class IvyyyBuildTowerRule : IvyyyRule
    {
        public IvyyyBuildTowerRule (TowerDefenseAgentState state) : base (state)
        {
        }

        public override void Action()
        {
            int defenseGrid = m_worldState.DefenseRerimeter;

            List<TowerPos> pos = new List<TowerPos>();
            GetTowerListForDefenseGrid(defenseGrid, ref pos);
            FilterTowerListForDefenseGrid(ref pos);

            int totalCost = GetTowerListCost(ref pos);
            //int enemyCountDefenseGrid = GetEnemyCount (0, 0, 9, 7);
            int towerCount = m_worldState.Player.HomeLane.TowerCount() + pos.Count;

            if (totalCost < m_worldState.Player.Gold/* && enemyCountDefenseGrid <= towerCount*/)
                PlaceTower(pos);
            else
                DebugLogger.Log("#Player" + m_worldState.Player.Name + " Abandon Defense!");
        }

        private int GetEnemyCount(int startIndex)
        {
            return GetEnemyCount(startIndex, 0, 2, 3);
        }

        private int GetEnemyCount(int startX, int startY, int rCount, int cCount)
        {
            int count = 0;

            for (int r = 0; r < rCount; ++r)
            {
                for (int c = 0; c < cCount; ++c)
                {
                    Cell cell = m_worldState.Player.HomeLane.GetCellAt(startX + c, startY + r);

                    if (cell.Unit != null)
                        count++;
                }
            }

            return count;
        }

        private void GetTowerListForDefenseGrid(int grid, ref List<TowerPos> towerList)
        {
            if (grid == 0)
            {
                towerList.Add(new TowerPos(2, 7));
                towerList.Add(new TowerPos(2, 5));
                towerList.Add(new TowerPos(3, 6));
                towerList.Add(new TowerPos(1, 6));
            }
            else if (grid == 2)
            {
                towerList.Add(new TowerPos(4, 7));
                towerList.Add(new TowerPos(4, 5));
                towerList.Add(new TowerPos(3, 6));
                towerList.Add(new TowerPos(5, 6));
            }
            else
            {
                towerList.Add(new TowerPos(3, 6));
                towerList.Add(new TowerPos(2, 5));
                towerList.Add(new TowerPos(4, 5));
                towerList.Add(new TowerPos(3, 4));
            }
        }

        private void FilterTowerListForDefenseGrid(ref List<TowerPos> towerList)
        {
            List<TowerPos> newList = new();

            for (int i = 0; i < towerList.Count; ++i)
            {
                TowerPos towerPos = towerList[i];

                if (m_worldState.Player.HomeLane.GetCellAt(towerPos.x, towerPos.y).Unit == null)
                    newList.Add(towerPos);
            }

            while (newList.Count > 3)
                newList.RemoveAt(newList.Count - 1);

            towerList = newList;
        }

        private int GetTowerListCost(ref List<TowerPos> towerList)
        {
            int cost = 0;
            int towerCount = m_worldState.Player.HomeLane.TowerCount();

            for (int i = 0; i < towerList.Count; ++i)
                cost += 2 + towerCount + i;

            return cost;
        }

        private void PlaceTower(List<TowerPos> positions)
        {
            for (int i = 0; i < positions.Count; ++i)
            {
                TowerPos pos = positions[i];
                m_worldState.Player.TryBuyTower<Tower>(pos.x, pos.y);
            }
        }

        public override bool MatchRule(IvyyyStrategy.Goal goal)
        {
            return goal == IvyyyStrategy.Goal.BuildTower
                && m_worldState.ActionTyp == TowerDefensePerception.ActionTyp.DeployTowers;
        }
    }
}
