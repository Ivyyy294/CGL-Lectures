using GameFramework;
using System.Collections.Generic;

namespace IvyyyAI
{
    public class IvyyyBuildTowerRule : IvyyyRule
    {
        public IvyyyBuildTowerRule (IvyyyWorldState state) : base (state)
        {
            m_target = "TowerBlocks";

            //m_axis.Add (new IvyyyRuleAxis("TowerCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.75f, 1f, 1f, 0f)));
            //m_axis.Add (new IvyyyRuleAxis("GoldCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 0.2f, 1f, 0.8f, 0f)));
            //m_axis.Add (new IvyyyRuleAxis("EnemyCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -1f, 2f, 1f, 1f)));

            m_axis.Add (new IvyyyRuleAxis("TargetsInReach", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 1f, 3f, 0f, 0f)));
            m_axis.Add (new IvyyyRuleAxis("FreeTowerSlots", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 1f, 4f, 0f, 0f)));
            m_axis.Add (new IvyyyRuleAxis("ThreatenedCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.5f, 2.0f, 1f, 0f)));
            //m_axis.Add (new IvyyyRuleAxis("EnemyInBlockCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.75f, 1f, 1f, 0f)));

            m_axis.Add (new IvyyyRuleAxis ("CanBuyTowers", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear)));

            m_weight = 5f;
        }

        public override void Action(object target)
        {
            DebugLogger.Log("#Player" + m_worldState.Player.Name + " Build Tower!");

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
