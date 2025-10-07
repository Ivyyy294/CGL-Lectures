using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AI_Strategy
{
    internal struct TowerPos
    {
        public int x;
        public int y;

        public TowerPos (int xPos, int yPos)
        {
            x = xPos;
            y = yPos;
        }
    }

    public class DeployTowerState: StrategyState
    {
        public DeployTowerState (StrategyStateMachine stateMachine) : base(stateMachine)
        {
        }

        public override void Continue()
        {
        }

        public override void DeploySoldiers()
        {
        }

        public override void DeployTowers()
        {
            int defenseGrid = GetSecondaryDefenseGrid();

            List<TowerPos> pos = new List<TowerPos>();
            GetTowerListForDefenseGrid (defenseGrid, ref pos);
            FilterTowerListForDefenseGrid (ref pos);

            int totalCost = GetTowerListCost (ref pos);
            int enemyCountDefenseGrid = GetEnemyCount (0, 0, 9, 7);
            int towerCount = m_player.HomeLane.TowerCount() + pos.Count;

            if (totalCost < m_player.Gold && enemyCountDefenseGrid <= towerCount)
                PlaceTower (pos);
            else
                DebugLogger.Log("#Player" + m_player.Name + " Abandon Defense!");

            m_stateMachine.Pop();
        }

        public override void Enter()
        {
            DebugLogger.Log("#Player" + m_player.Name + " Build Defense!");
        }

        public override void Exit()
        {
        }

        private int GetSecondaryDefenseGrid ()
        {
            int cLeft = GetEnemyCount(0);
            int cCenter = GetEnemyCount(2);
            int cRight = GetEnemyCount(4);

            if (cLeft > cCenter && cLeft > cRight)
                return 0;
            else if (cRight > cLeft && cRight > cCenter)
                return 2;
            else
                return 1;
        }

        private int GetEnemyCount(int startIndex)
        {
            return GetEnemyCount (startIndex, 0, 2, 3);
        }

        private int GetEnemyCount(int startX, int startY, int rCount, int cCount)
        {
            int count = 0;

            for (int r = 0; r < rCount; ++r)
            {
                for (int c = 0; c < cCount; ++c)
                {
                    Cell cell = m_player.HomeLane.GetCellAt(startX + c, startY + r);

                    if (cell.Unit != null)
                        count++;
                }
            }

            return count;
        }

        private void GetTowerListForDefenseGrid (int grid, ref List<TowerPos> towerList)
        {
            if (grid == 0)
            {
                towerList.Add (new TowerPos (2,7));
                towerList.Add (new TowerPos (2,5));
                towerList.Add (new TowerPos (3,6));
                towerList.Add (new TowerPos (1,6));
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

                if (m_player.HomeLane.GetCellAt(towerPos.x, towerPos.y).Unit == null)
                    newList.Add(towerPos);
            }

            while (newList.Count > 3)
                newList.RemoveAt(newList.Count-1);

            towerList = newList;
        }

        private int GetTowerListCost(ref List<TowerPos> towerList)
        {
            int cost = 0;
            int towerCount = m_player.HomeLane.TowerCount();

            for (int i = 0; i < towerList.Count; ++i)
                cost += 2 + towerCount + i;

            return cost;
        }

        private void PlaceTower (List<TowerPos> positions)
        {
            for (int i = 0; i < positions.Count; ++i)
            {
                TowerPos pos = positions[i];
                m_player.TryBuyTower<Tower>(pos.x, pos.y);
            }
        }
    }
}
