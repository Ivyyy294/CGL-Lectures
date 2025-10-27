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
            m_target = "TowerBlocks";

            m_inputParameter.Add ("TargetsInReach");
            m_inputParameter.Add ("CanBuyTowers");
            m_inputParameter.Add ("DeployTowers");
            m_inputParameter.Add ("FreeTowerSlots");
            m_inputParameter.Add ("ThreatenedCount");
            m_inputParameter.Add ("EnemyInBlockCount");
            m_weight = 5f;
        }

        public override void Action(object target)
        {
            IvyyyTowerBlock towerBlock = (IvyyyTowerBlock) target;
            List<IvyyyPosition> pos = towerBlock.TowerSlots;

            FilterTowerListForDefenseGrid(ref pos);

            PlaceTower(pos);
        }

        private void FilterTowerListForDefenseGrid(ref List<IvyyyPosition> towerList)
        {
            List<IvyyyPosition> newList = new();

            for (int i = 0; i < towerList.Count; ++i)
            {
                IvyyyPosition towerPos = towerList[i];

                if (m_worldState.Player.HomeLane.GetCellAt(towerPos.x, towerPos.y).Unit == null)
                    newList.Add(towerPos);
            }

            towerList = newList;
        }

        private void PlaceTower(List<IvyyyPosition> positions)
        {
            for (int i = 0; i < positions.Count; ++i)
            {
                IvyyyPosition pos = positions[i];
                m_worldState.Player.TryBuyTower<Tower>(pos.x, pos.y);
            }
        }
    }
}
