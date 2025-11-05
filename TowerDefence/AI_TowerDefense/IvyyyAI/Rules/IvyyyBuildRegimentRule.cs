using Agent_Test;
using GameFramework;
using tower_defence.AI_TowerDefense.IvyyyAI;

namespace AI_Strategy
{
    public class IvyyyBuildRegimentRule : IvyyyRule
    {
        public IvyyyBuildRegimentRule(TowerDefenseAgentState state) : base(state)
        {
            m_axis.Add(new IvyyyRuleAxis("GoldCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, -0.75f, 1f, 1f, 0f)));
            m_axis.Add(new IvyyyRuleAxis("TowerCount", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear, 0.5f, 1f, 0.5f, 0f)));
            //m_axis.Add (new IvyyyRuleAxis ("CanBuySoldiers", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.Linear)));
            m_axis.Add (new IvyyyRuleAxis ("DeploySoldiers", new IvyyyResponseCurve(IvyyyResponseCurve.CurveType.None)));
        }

        public override void Action(object target)
        {
            DebugLogger.Log("#Player" + m_worldState.Player.Name + " Build Regiment!");

            ActiveRegimentSettings activeRegimentSettings = m_worldState.ActiveRegimentSettings;
            
            if (m_worldState.Gold < activeRegimentSettings.Width * 2)
                return;

            for (int i = 0; i < activeRegimentSettings.Width; ++i)
            {
                int xPos = activeRegimentSettings.StartIndex + i;
                Player.SoldierPlacementResult result = m_worldState.Player.TryBuySoldier<IvyyySoldier>(xPos);

                if (result == Player.SoldierPlacementResult.Success)
                {
                    Cell cell = m_worldState.Player.EnemyLane.GetCellAt(xPos, 0);
                    IvyyySoldier soldier = (IvyyySoldier)cell.Unit;
                    activeRegimentSettings.m_soldiers.Add(soldier);
                }
            }

        }
    }
}
