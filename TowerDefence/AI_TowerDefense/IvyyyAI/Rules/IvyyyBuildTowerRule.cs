using GameFramework;
using System.Collections.Generic;

namespace IvyyyAI
{
    public class IvyyyBuildTowerRule : IvyyyRule
    {
        public IvyyyBuildTowerRule (IvyyyWorldState state) : base (state)
        {
            m_target = "TowerBlocks";

            //Reduces the score with growing tower numbers
            m_axis.Add(new IvyyyRuleAxis("TowerCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Logistic, 100f, -1f, 1f, 0.5f)));

            //Reduces the score if fewer targets are in reach
            m_axis.Add (new IvyyyRuleAxis("TargetsInReach", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Logistic, 500f, 1f, 0f, 0.5f)));

            //Reduces the score if tower slots are ocupied
            m_axis.Add (new IvyyyRuleAxis("FreeTowerSlots", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -1f, 8f, 1f, 1f)));

            //Ensures we only build towrs during place tower phase
            m_axis.Add (new IvyyyRuleAxis ("DeployTower", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.None)));

            //Ensures we have enough gold to build the required towers
            m_axis.Add (new IvyyyRuleAxis ("CanBuyTowers", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Logistic, 500.0f, 1.0f, 0f, 0.5f)));

            //Reduces the score for blocks with lower possible tower count
            m_axis.Add (new IvyyyRuleAxis ("TowerSpace", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -1f, 2f, 1f, 1f)));

            m_weight = 10f;
        }


        public override void Action(object target)
        {
            DebugLogger.Log("#Player" + m_worldState.Player.Name + " Build Tower!");

            IvyyyTowerBlock towerBlock = (IvyyyTowerBlock) target;
            List<IvyyyPosition> pos = towerBlock.TowerSlots;

            FilterTowerListForDefenseGrid(ref pos);

            PlaceTower(pos);
        }

        //Removes blocked tower positions from list
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

        //Places towers on provides positions
        private void PlaceTower(List<IvyyyPosition> positions)
        {
            for (int i = 0; i < positions.Count; ++i)
            {
                IvyyyPosition pos = positions[i];
                m_worldState.Player.TryBuyTower<GongiTower>(pos.x, pos.y);
            }
        }
    }
}
