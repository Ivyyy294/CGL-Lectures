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
            m_inputParameter.Add ("CanBuyTowers");
            m_inputParameter.Add ("ValidTowerSpot");
            m_inputParameter.Add ("DeployTowers");
            m_weight = 5f;
        }

        public override void Action()
        {
            List<TowerPos> pos = new List<TowerPos>();
            GetTowerListForDefenseGrid(ref pos);
            FilterTowerListForDefenseGrid(ref pos);

            int totalCost = GetTowerListCost(ref pos);
            int towerCount = m_worldState.Player.HomeLane.TowerCount() + pos.Count;

            PlaceTower(pos);

            //if (totalCost < m_worldState.Player.Gold)
            //    PlaceTower(pos);
            //else
            //    DebugLogger.Log("#Player" + m_worldState.Player.Name + " Abandon Defense!");
        }

        private void GetTowerListForDefenseGrid(ref List<TowerPos> towerList)
        {
            TowerDefensePerimeter perimeter = m_worldState.BestDefensePerimeter;

            towerList.Add(new TowerPos(perimeter.X + 1, perimeter.Y));
            towerList.Add(new TowerPos(perimeter.X + 1, perimeter.Y + 2));

            if (perimeter.X > 0)
            {
                towerList.Add(new TowerPos(perimeter.X, perimeter.Y + 1));
                towerList.Add(new TowerPos(perimeter.X + 2, perimeter.Y + 1));
            }
            else
            {
                towerList.Add(new TowerPos(perimeter.X + 2, perimeter.Y + 1));
                towerList.Add(new TowerPos(perimeter.X, perimeter.Y + 1));
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
    }
}
